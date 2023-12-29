#include "DirectoryEntry.h"

#include <iostream>
#include <magic_enum.hpp>

#include "GeometryEntry.h"
#include "GroupEntry.h"
#include "LocalizedEntry.h"
#include "MaterialEntry.h"
#include "Serializer.h"
#include "TextEntry.h"
#include "TransformEntry.h"

std::shared_ptr<Entry> DirectoryEntry::Remove(const EntryPath &path,
                                              EntryPath parent) {
    auto name = path.GetName();
    if (auto it = _nameToIndex.find(name); it != _nameToIndex.end()) {
        auto next = path.GetNext();
        if (next.IsValid()) {
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(
                    _entries[it->second].second);
                dir) {
                return dir->Remove(next, parent.Append(name));
            } else {
                std::cerr << "Can't remove " << path.Path << " because entry "
                          << name << " is not a directory." << std::endl;
                return {};
            }
        } else {
            auto index = it->second;
            auto entry = _entries[index].second;
            _entries.erase(_entries.begin() + index);
            _nameToIndex.erase(it);

            auto root = parent.Append(name);
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry);
                dir) {
                dir->TraverseDownTop([&](auto сname, auto centry) {
                    auto cpath = root.Append(сname.Path);
                    OnEntryRemoved(cpath, centry);
                });
            }

            OnEntryRemoved(root, entry);
            return entry;
        }
    } else {
        std::cerr << "Can't remove " << path.Path << " because entry " << name
                  << " not found." << std::endl;
        return {};
    }
}

void DirectoryEntry::TraverseTopDown(
    const EntryPath &parent,
    std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
    for (auto &[name, entry] : _entries) {
        cb(parent.Append(name), entry);

        if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry); dir) {
            dir->TraverseTopDown(parent.Append(name), cb);
        }
    }
}

void DirectoryEntry::TraverseDownTop(
    const EntryPath &parent,
    std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
    for (auto &[name, entry] : _entries) {
        if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry); dir) {
            dir->TraverseDownTop(parent.Append(name), cb);
        }

        cb(parent.Append(name), entry);
    }
}

bool DirectoryEntry::Add(const EntryPath &path, EntryPath parent,
                         std::shared_ptr<Entry> entry) {
    auto name = path.GetName();
    auto next = path.GetNext();

    if (next.IsValid()) {
        auto it = _nameToIndex.find(name);
        if (it == _nameToIndex.end()) {
            auto group = std::make_shared<GroupEntry>();
            CopyObserversTo(*group);
            _nameToIndex[name] = _entries.size();
            _entries.push_back({name, std::static_pointer_cast<Entry>(group)});
            group->SetParent(shared_from_this());

            OnEntryAdded(parent.Append(name), group);
            group->Add(next, parent.Append(name), entry);
        } else {
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(
                    _entries[it->second].second);
                dir) {
                dir->Add(next, parent.Append(name), entry);
            } else {
                std::cerr << "Can't add "
                          << magic_enum::enum_name(entry->GetType()) << " to "
                          << parent.Path << ". Parent is not a directory."
                          << std::endl;
                return false;
            }
        }
    } else {
        auto it = _nameToIndex.find(name);
        if (it == _nameToIndex.end()) {
            _nameToIndex[name] = _entries.size();
            _entries.push_back({name, entry});
            CopyObserversTo(*entry);
            entry->SetParent(shared_from_this());
            OnEntryAdded(parent.Append(name), entry);

            auto root = parent.Append(name);
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry);
                dir) {
                dir->TraverseTopDown([&](auto localPath, auto сentry) {
                    auto сpath = root.Append(localPath.Path);
                    CopyObserversTo(*сentry);
                    OnEntryAdded(сpath, сentry);
                });
            } else {
            }
        } else {
            std::cout << "Can't add " << magic_enum::enum_name(entry->GetType())
                      << " to " << parent.Path << ". Already exists."
                      << std::endl;
            return false;
        }
    }
    return false;
}

DirectoryEntry::DirectoryEntry() {}

// DirectoryEntry::DirectoryEntry(const DirectoryEntry& entry) : Entry{entry} {
//     for (auto [name, entry] : entry._entries) {
//         _entries[name] = entry->Clone();
//     }
// }

std::shared_ptr<Entry> DirectoryEntry::FindEntry(const EntryPath &path) const {
    auto name = path.GetName();
    if (auto it = _nameToIndex.find(name); it != _nameToIndex.end()) {
        auto next = path.GetNext();
        if (next.IsValid()) {
            if (auto dir = std::dynamic_pointer_cast<DirectoryEntry>(
                    _entries[it->second].second);
                dir) {
                return dir->FindEntry(next);
            } else {
                std::cerr << "Failed to find entry " << path.Path << std::endl;
            }
        } else {
            return _entries[it->second].second;
        }
    } else {
        std::cerr << "Failed to find entry " << path.Path << std::endl;
    }
    return {};
}

void DirectoryEntry::Serialize(EntryProperties &properties) const {
    Entry::Serialize(properties);
    EntryProperties entries;
    for (auto [name, entry] : _entries) {
        EntryProperties d;
        d["Name"] = name;
        entry->Serialize(d["Data"]);
        entries.push_back(std::move(d));
    }
    properties["Entries"] = std::move(entries);
}

void DirectoryEntry::DeserializeInternal(EntryPath path,
                                         const EntryProperties &properties) {
    Entry::DeserializeInternal(path, properties);
    if (auto it = properties.find("Entries"); it == properties.end())
        return;
    else
        for (auto entry : *it) {
            auto name = ::Deserialize(entry, "Name", std::string{});
            if (auto dit = entry.find("Data"); dit == entry.end())
                continue;
            else {
                auto type = ::Deserialize(*dit, "Type", std::string{});
                std::shared_ptr<Entry> newEntry;
                if (type == magic_enum::enum_name(EntryType::Transform)) {
                    newEntry =
                        std::make_shared<TransformProxyEntry>(EntryPath{});
                } else if (type == magic_enum::enum_name(EntryType::Geometry)) {
                    newEntry =
                        std::make_shared<GeometryProxyEntry>(EntryPath{});
                } else if (type == magic_enum::enum_name(EntryType::Material)) {
                    newEntry =
                        std::make_shared<MaterialProxyEntry>(EntryPath{});
                } else if (type == magic_enum::enum_name(EntryType::Group)) {
                    newEntry = std::make_shared<GroupEntry>();
                } else if (type ==
                           magic_enum::enum_name(EntryType::Localized)) {
                    newEntry = std::make_shared<LocalizedEntry>();
                } else if (type == magic_enum::enum_name(EntryType::Text)) {
                    newEntry = std::make_shared<TextEntry>();
                }

                if (!newEntry) {
                    std::cout << "Can't deserialize " << name << " of type "
                              << type << std::endl;
                    continue;
                }

                _nameToIndex[name] = _entries.size();
                _entries.push_back({name, newEntry});
                CopyObserversTo(*newEntry);
                newEntry->SetParent(shared_from_this());
                OnEntryAdded(path.Append(name), newEntry);

                newEntry->DeserializeInternal(path.Append(name), *dit);
            }
        }
}

void DirectoryEntry::CloneFrom(std::shared_ptr<Entry> entry) {
    Entry::CloneFrom(entry);

    assert(std::dynamic_pointer_cast<DirectoryEntry>(entry));
    auto dir = std::static_pointer_cast<DirectoryEntry>(entry);

    for (auto [name, сentry] : dir->_entries) {
        auto e = сentry->Clone();
        e->SetParent(shared_from_this());
        CopyObserversTo(*e);
        _nameToIndex[name] = _entries.size();
        _entries.push_back({name, e});
    }
}
