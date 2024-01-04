#pragma once

#include <functional>
#include <iostream>
#include <magic_enum.hpp>
#include <mutex>
#include <unordered_map>

#include "Entry.h"
#include "EntryPath.h"
#include "IDirectoryEntry.h"
#include "IEntry.h"
#include "IEntryObserver.h"
#include "IGroupEntry.h"
#include "Observer.h"

namespace Vandrouka {

template <typename Derived, typename... Interfaces>
class DirectoryEntryBase
    : public EntryBase<Derived, IDirectoryEntry, IObservable, Interfaces...> {

  // using Base = EntryBase<Derived, IDirectoryEntry, IObservable,
  // Interfaces...>;

  std::unordered_map<std::string, size_t> _nameToIndex;
  std::vector<std::pair<std::string, EntryRef>> _entries;

public:
  // bool QueryInterface(const InterfaceId &id, void **o) override {
  //   if (id == GetIID<IObservable>::Id) {
  //     *o = static_cast<IObservable *>(this);
  //   } else if (id == GetIID<IDirectoryEntry>::Id) {
  //     *o = static_cast<IDirectoryEntry *>(this);
  //   } else if (id == GetIID<IEntry>::Id) {
  //     *o = static_cast<IEntry *>(this);
  //   } else if (id == GetIID<IReferenced>::Id) {
  //     *o = static_cast<IReferenced *>(static_cast<IDirectoryEntry *>(this));
  //   } else {
  //     *o = nullptr;
  //   }

  //   if (*o) {
  //     this->AddRef();
  //   }

  //   return *o != nullptr;
  // }

  void ForEachEntry(
      std::function<void(const std::string &name, EntryRef)> cb) override {
    for (auto &[name, entry] : _entries) {
      cb(name, entry);
    }
  }

  bool IsEmpty() const override { return _entries.empty(); }

  bool CanAdd(EntryRef) override { return true; }

  EntryRef FindEntry(const EntryPath &path) const override {
    auto name = path.GetName();
    if (auto it = this->_nameToIndex.find(name);
        it != this->_nameToIndex.end()) {
      auto next = path.GetNext();
      if (next.IsValid()) {
        if (auto dir =
                this->_entries[it->second].second.Cast<IDirectoryEntry>();
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

  bool Add(const EntryPath &path, EntryRef entry,
           const EntryPath &parent) override {
    auto name = path.GetName();
    auto next = path.GetNext();

    if (next.IsValid()) {
      auto it = _nameToIndex.find(name);
      if (it == _nameToIndex.end()) {
        auto group = Create<GroupEntry, IDirectoryEntry>();
        _nameToIndex[name] = _entries.size();
        _entries.push_back({name, group.Cast<IEntry>()});
        group->SetParent((Derived *)this);
        OnEntryAdded(parent.Append(name), group);
        group->Add(next, entry, parent.Append(name));
      } else {
        if (auto dir = _entries[it->second].second.Cast<IDirectoryEntry>();
            dir) {
          dir->Add(next, entry, parent.Append(name));
        } else {
          std::cerr << "Can't add " << magic_enum::enum_name(entry->GetType())
                    << " to " << parent.Path << ". Parent is not a directory."
                    << std::endl;
          return false;
        }
      }
    } else {
      auto it = _nameToIndex.find(name);
      if (it == _nameToIndex.end()) {
        _nameToIndex[name] = _entries.size();
        _entries.push_back({name, entry});
        // CopyObserversTo(*entry);
        entry->SetParent(this);
        OnEntryAdded(parent.Append(name), entry);

        auto root = parent.Append(name);
        if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
          dir->TraverseTopDown([&](auto localPath, auto сentry) {
            auto сpath = root.Append(localPath.Path);
            // CopyObserversTo(*сentry);
            OnEntryAdded(сpath, сentry);
          });
        } else {
        }
      } else {
        std::cout << "Can't add " << magic_enum::enum_name(entry->GetType())
                  << " to " << parent.Path << ". Already exists." << std::endl;
        return false;
      }
    }
    return false;
  }

  void TraverseTopDown(std::function<void(EntryPath path, EntryRef)> cb,
                       const EntryPath &parent) override {
    for (auto &[name, entry] : _entries) {
      cb(parent.Append(name), entry);

      if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
        dir->TraverseTopDown(cb, parent.Append(name));
      }
    }
  }

  void TraverseDownTop(std::function<void(EntryPath path, EntryRef)> cb,
                       const EntryPath &parent) override {
    for (auto &[name, entry] : _entries) {
      if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
        dir->TraverseDownTop(cb, parent.Append(name));
      }

      cb(parent.Append(name), entry);
    }
  }

  EntryRef Remove(const EntryPath &path, const EntryPath &parent) override {
    auto name = path.GetName();
    if (auto it = _nameToIndex.find(name); it != _nameToIndex.end()) {
      auto next = path.GetNext();
      if (next.IsValid()) {
        if (auto dir = _entries[it->second].second.Cast<IDirectoryEntry>();
            dir) {
          return dir->Remove(next, parent.Append(name));
        } else {
          std::cerr << "Can't remove " << path.Path << " because entry " << name
                    << " is not a directory." << std::endl;
          return {};
        }
      } else {
        auto index = it->second;
        auto entry = _entries[index].second;
        _entries.erase(_entries.begin() + index);
        _nameToIndex.erase(it);

        auto root = parent.Append(name);
        if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
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

  class EntryAddedMessage
      : public MessageBase<EntryAddedMessage, IEntryAddedMessage> {
  public:
    EntryAddedMessage(EntryPath path, EntryRef entry)
        : _path{path}, _entry{entry} {}

    EntryPath GetPath() const override { return this->_path; }

    EntryRef GetEntry() const override { return this->_entry; }

  private:
    EntryPath _path;
    EntryRef _entry;
  };

  void OnEntryAdded(EntryPath path, EntryRef entry) {
    this->OnMessage(new EntryAddedMessage{path, entry});
  }

  class EntryRemovedMessage
      : public MessageBase<EntryRemovedMessage, IEntryRemovedMessage> {
  public:
    EntryRemovedMessage(EntryPath path, EntryRef entry)
        : _path{path}, _entry{entry} {}

    EntryPath GetPath() const override { return this->_path; }

    EntryRef GetEntry() const override { return this->_entry; }

  private:
    EntryPath _path;
    EntryRef _entry;
  };

  void OnEntryRemoved(EntryPath path, EntryRef entry) {
    this->OnMessage(new EntryRemovedMessage{path, entry});
  }
};

} // namespace Vandrouka

class DirectoryEntry : public Entry {
  std::unordered_map<std::string, size_t> _nameToIndex;
  std::vector<std::pair<std::string, std::shared_ptr<Entry>>> _entries;

public:
  DirectoryEntry();
  // DirectoryEntry(const DirectoryEntry& entry);

  void ForEachEntry(
      std::function<void(const std::string &name, std::shared_ptr<Entry>)> cb) {
    for (auto &[name, entry] : _entries) {
      cb(name, entry);
    }
  }

  void TraverseTopDown(
      std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
    TraverseTopDown({}, cb);
  }

  void TraverseDownTop(
      std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
    TraverseDownTop({}, cb);
  }

  bool IsEmpty() const { return _entries.empty(); }

  bool Add(const EntryPath &path, std::shared_ptr<Entry> entry) {
    if (!CanAdd(entry))
      return false;

    return Add(path, {}, entry);
  }

  std::shared_ptr<Entry> Remove(const EntryPath &path) {
    return Remove(path, {});
  }

  std::shared_ptr<Entry> FindEntry(const EntryPath &path) const override;

  void Serialize(EntryProperties &properties) const override;

protected:
  virtual bool CanAdd(std::shared_ptr<Entry> entry) = 0;
  void DeserializeInternal(EntryPath path,
                           const EntryProperties &properties) override;
  void CloneFrom(std::shared_ptr<Entry> entry) override;

private:
  bool Add(const EntryPath &path, EntryPath parent,
           std::shared_ptr<Entry> entry);
  std::shared_ptr<Entry> Remove(const EntryPath &path, EntryPath parent);
  void TraverseTopDown(
      const EntryPath &parent,
      std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
  void TraverseDownTop(
      const EntryPath &parent,
      std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
};
