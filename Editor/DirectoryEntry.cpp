#include <iostream>
#include <magic_enum.hpp>
#include "DirectoryEntry.h"
#include "GroupEntry.h"

std::shared_ptr<Entry> DirectoryEntry::Remove(const EntryPath& path, EntryPath parent, IDirectoryObserver& o) {
    std::unique_lock lock{ _cs };
    auto name = path.GetName();
    if (auto it = _entries.find(name); it != _entries.end()) {
        auto next = path.GetNext();
        if (next.IsValid()) {
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(it->second); dir) {
                return dir->Remove(next, parent.Append(name), o);
            }
            else {
                std::cerr << "Can't remove " << path.Path << " because entry " << name << " is not a directory." << std::endl;
                return {};
            }
        }
        else {
            auto entry = it->second;
            _entries.erase(it);
            auto root = parent.Append(name);
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry); dir) {
                dir->TraverseDownTop([&](auto name, auto entry) {
                    auto path = root.Append(name.Path);
                    o.OnEntryRemoved(path, entry);
                    });
            }

            o.OnEntryRemoved(root, entry);
            return entry;
        }
    }
    else {
        std::cerr << "Can't remove " << path.Path << " because entry " << name << " not found." << std::endl;
        return {};
    }
}

void DirectoryEntry::TraverseTopDown(const EntryPath& parent, std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
    std::unique_lock lock{ _cs };
    for (auto& [name, entry] : _entries) {
        cb(parent.Append(name), entry);

        if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry); dir) {
            dir->TraverseTopDown(parent.Append(name), cb);
        }
    }
}

void DirectoryEntry::TraverseDownTop(const EntryPath& parent, std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
    std::unique_lock lock{ _cs };
    for (auto& [name, entry] : _entries) {

        if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry); dir) {
            dir->TraverseDownTop(parent.Append(name), cb);
        }

        cb(parent.Append(name), entry);
    }
}

void DirectoryEntry::Add(const EntryPath& path, EntryPath parent, std::shared_ptr<Entry> entry, IDirectoryObserver& o)
{
    std::unique_lock lock{ _cs };
    auto name = path.GetName();
    auto next = path.GetNext();

    if (next.IsValid()) {
        auto it = _entries.find(name);
        if (it == _entries.end()) {
            auto group = std::make_shared<GroupEntry>();
            _entries[name] = group;
            group->SetParent(shared_from_this());

            o.OnEntryAdded(parent.Append(name), group);
            group->Add(next, parent.Append(name), entry, o);
        }
        else {
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(it->second); dir) {
                dir->Add(next, parent.Append(name), entry, o);
            }
            else {
                std::cerr << "Can't add " << magic_enum::enum_name(entry->GetType()) << " to " << parent.Path << ". Parent is not a directory." << std::endl;
            }
        }
    }
    else {
        auto it = _entries.find(name);
        if (it == _entries.end()) {
            _entries[name] = entry;
            entry->SetParent(shared_from_this());
            o.OnEntryAdded(parent.Append(name), entry);

            auto root = parent.Append(name);
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry); dir) {
                dir->TraverseTopDown([&](auto localPath, auto entry) {
                    auto path = root.Append(localPath.Path);
                    o.OnEntryAdded(path, entry);
                    });
            }
            else {
            }
        }
        else {
            std::cout << "Can't add " << magic_enum::enum_name(entry->GetType()) << " to " << parent.Path << ". Already exists." << std::endl;
        }
    }
}


std::shared_ptr<Entry> DirectoryEntry::FindEntry(const EntryPath& path) const {
    std::unique_lock lock{ _cs };

    auto name = path.GetName();
    if (auto it = _entries.find(name); it != _entries.end()) {
        auto next = path.GetNext();
        if (next.IsValid()) {
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(it->second); dir) {
                return dir->FindEntry(next);
            }
            else {
                std::cerr << "Failed to find entry " << path.Path << std::endl;
            }
        }
        else {
            return it->second;
        }
    }
    else {
        std::cerr << "Failed to find entry " << path.Path << std::endl;
    }
    return {};
}
