#pragma once

#include <functional>
#include <iostream>
#include <magic_enum.hpp>
#include <mutex>
#include <string>
#include <unordered_map>

#include "Entry.h"
#include "EntryPath.h"
#include "IDirectoryEntry.h"
#include "IEntry.h"
#include "IEntryObserver.h"
#include "IGeometryEntry.h"
#include "IGroupEntry.h"
#include "ILocalizedEntry.h"
#include "IMaterialEntry.h"
#include "IPackageEntry.h"
#include "ISerializable.h"
#include "ITextEntry.h"
#include "ITransformEntry.h"
#include "Messages/EntryAddedMessage.h"
#include "Messages/EntryRemovedMessage.h"
#include "Observer.h"

namespace Vandrouka {

class IDirectoryEntryPrivate : public IDirectoryEntry {
public:
  virtual Result<void> AddInternal(const EntryPath &path, EntryRef entry,
                                   const EntryPath &parent,
                                   DirectoryChanges &changes) = 0;

  virtual Result<void> RemoveInternal(const EntryPath &path,
                                      const EntryPath &parent,
                                      DirectoryChanges &changes) = 0;
};

template <> struct GetIID<IDirectoryEntryPrivate> {
  static constexpr InterfaceId Id = {{0x30, 0xf0, 0x79, 0xfa, 0xa8, 0x47, 0x4f,
                                      0x32, 0xac, 0xb0, 0xc, 0x31, 0xd, 0x4b,
                                      0x5a, 0x78}};
};

template <typename Derived, typename... I>
class DirectoryEntryBase
    : public EntryBase<Derived, IDirectoryEntryPrivate, ISerializable, I...> {

  using Base = EntryBase<Derived, IDirectoryEntryPrivate, ISerializable, I...>;

  // Interfaces...>;

  std::unordered_map<std::string, size_t> _nameToIndex;
  std::vector<std::pair<std::string, EntryRef>> _entries;

public:
  using Interfaces =
      QueryInterfaces<Derived, I..., IDirectoryEntry, IDirectoryEntryPrivate,
                      IEntry, ISerializable, IReferenced>;

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

  Result<DirectoryChanges> Add(const EntryPath &path, EntryRef entry) override {
    DirectoryChanges changes;
    if (auto result = this->AddInternal(path, entry, {}, changes); result) {
      return {changes};
    } else {
      return result.Error();
    }
  }

  Result<void> AddInternal(const EntryPath &path, EntryRef entry,
                           const EntryPath &parent,
                           DirectoryChanges &changes) override {
    auto name = path.GetName();
    auto next = path.GetNext();

    if (next.IsValid()) {
      auto it = _nameToIndex.find(name);
      if (it == _nameToIndex.end()) {
        auto group = Create<GroupEntry, IDirectoryEntryPrivate>();
        _nameToIndex[name] = _entries.size();
        _entries.push_back({name, group.Cast<IEntry>()});
        group->SetParent((Derived *)this);
        changes.Added.push_back(
            new EntryAddedMessage{parent.Append(name), group, this});
        // OnEntryAdded(parent.Append(name), group);
        group->AddInternal(
            next, entry, parent.Append(name), changes);
      } else {
        if (auto dir = _entries[it->second].second.Cast<IDirectoryEntry>();
            dir) {
          return dir.Cast<IDirectoryEntryPrivate>()->AddInternal(
              next, entry, parent.Append(name), changes);
        } else {
          return {new GenericError{
              LOG_LEVEL_ERROR, LOG_TYPE_MISMATCH,
              std::string("Can't add ") +
                  std::string(magic_enum::enum_name(entry->GetType())) +
                  " to " + parent.Path + ". Parent is not a directory."}};
        }
      }
    } else {
      auto it = _nameToIndex.find(name);
      if (it == _nameToIndex.end()) {
        _nameToIndex[name] = _entries.size();
        _entries.push_back({name, entry});
        // CopyObserversTo(*entry);
        entry->SetParent(this);

        changes.Added.push_back(
            new EntryAddedMessage{parent.Append(name), entry, this});
        // OnEntryAdded(parent.Append(name), entry);

        auto root = parent.Append(name);
        if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
          dir->TraverseTopDown([&](auto localPath, auto centry) {
            auto cpath = root.Append(localPath.Path);
            // CopyObserversTo(*сentry);
            changes.Added.push_back(new EntryAddedMessage{cpath, centry, dir});
            // OnEntryAdded(cpath, centry);
          });
        } else {
        }
      } else {
        return {new GenericError{
            LOG_LEVEL_ERROR, LOG_ENTRY_ALREADY_EXISTS,
            std::string("Can't add ") +
                std::string(magic_enum::enum_name(entry->GetType())) + " to " +
                parent.Path + ". Already exists."}};
      }
    }
    return {};
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

  Result<DirectoryChanges> Remove(const EntryPath &path) override {
    DirectoryChanges changes;
    if (auto result = this->RemoveInternal(path, {}, changes); result) {
      return changes;
    } else {
      return result.Error();
    }
  }

  Result<void> RemoveInternal(const EntryPath &path, const EntryPath &parent,
                              DirectoryChanges &changes) override {
    auto name = path.GetName();
    if (auto it = _nameToIndex.find(name); it != _nameToIndex.end()) {
      auto next = path.GetNext();
      if (next.IsValid()) {
        if (auto dir = _entries[it->second].second.Cast<IDirectoryEntry>();
            dir) {
          return dir.Cast<IDirectoryEntryPrivate>()->RemoveInternal(
              next, parent.Append(name), changes);
        } else {
          return {new GenericError{LOG_LEVEL_ERROR, LOG_TYPE_MISMATCH,
                                   std::string("Can't remove ") + path.Path +
                                       " because entry " + name +
                                       " is not a directory."}};
        }
      } else {
        auto index = it->second;
        auto entry = _entries[index].second;
        _entries.erase(_entries.begin() + index);
        _nameToIndex.erase(it);

        auto root = parent.Append(name);
        if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
          dir->TraverseDownTop([&](auto cname, auto centry) {
            auto cpath = root.Append(cname.Path);
            changes.Removed.push_back(
                new EntryRemovedMessage(cpath, centry, dir));
          });
        }

        changes.Removed.push_back(new EntryRemovedMessage(root, entry, this));
      }
      return {};
    } else {
      return {new GenericError{LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                               "Can't remove " + path.Path + " because entry " +
                                   name + " not found."}};
    }
  }

  /*void OnEntryAdded(EntryPath path, EntryRef entry) {
    this->RaiseMessage(new EntryAddedMessage{path, entry, this});
  }


  void OnEntryRemoved(EntryPath path, EntryRef entry) {
    this->RaiseMessage(new EntryRemovedMessage{path, entry, this});
  }*/

  Result<Ref<IPackageWriter>>
  SerializeInternal(Ref<IPackageWriter> writer) const override {
    Base::SerializeInternal(writer);

    auto entries = writer->BeginArray("Entries");
    {
      for (auto [name, entry] : _entries) {
        auto package = entries->BeginPackage();
        {
          package->Write("Name", name);
          auto data = package->BeginPackage("Data").Value();
          entry.Cast<ISerializable>()->Serialize(data, {});
          package->EndPackage();
        }
        entries->EndPackage();
      }
    }
    writer->EndArray();
    return writer;
  }

  Result<Ref<IPackageReader>>
  DeserializeInternal(Ref<IEntryPathStateWrapper> state,
                      Ref<IPackageReader> reader) override {

    Base::DeserializeInternal(state, reader);

    auto r = reader->ReadArray("Entries");
    if (r) {
      for (int i = 0; i < r->GetSize(); ++i) {
        auto entry = r->PackageAt(i).Value();
        auto name = entry->ReadString("Name").Value();
        auto data = entry->ReadPackage("Data").Value();
        auto type = data->ReadString("Type").Value();
        Ref<IEntry> newEntry;
        if (type == magic_enum::enum_name(EntryType::Transform)) {
          newEntry = Create<TransformProxyEntry, IEntry>();
        } else if (type == magic_enum::enum_name(EntryType::Geometry)) {
          newEntry = Create<GeometryProxyEntry, IEntry>();
        } else if (type == magic_enum::enum_name(EntryType::Material)) {
          newEntry = Create<MaterialProxyEntry, IEntry>();
        } else if (type == magic_enum::enum_name(EntryType::Group)) {
          newEntry = Create<GroupEntry, IEntry>();
        } else if (type == magic_enum::enum_name(EntryType::Localized)) {
          newEntry = Create<LocalizedEntry, IEntry>();
        } else if (type == magic_enum::enum_name(EntryType::Text)) {
          newEntry = Create<TextEntry, IEntry>();
        }

        if (!newEntry) {
          continue;
          /*return {new GenericError{LOG_LEVEL_ERROR, LOG_IO_ERROR,
                                   "Can't deserialize " + name + " of type " +
                                       type}};*/
        }

        _nameToIndex[name] = _entries.size();
        _entries.push_back({name, newEntry});
        // CopyObserversTo(*newEntry);
        newEntry->SetParent(this);
        // OnEntryAdded(state->GetState()->Append(name), newEntry);

        auto oldPath = state->GetState()->Path;
        state->GetState()->Path = oldPath.append(name);
        newEntry.Cast<ISerializable>()->Deserialize(
            entry->ReadPackage("Data").Value(), state);
        state->GetState()->Path = oldPath;
      }
    }
    return reader;
  }
};

} // namespace Vandrouka

// class DirectoryEntry : public Entry {
//   std::unordered_map<std::string, size_t> _nameToIndex;
//   std::vector<std::pair<std::string, std::shared_ptr<Entry>>> _entries;
//
// public:
//   DirectoryEntry();
//   // DirectoryEntry(const DirectoryEntry& entry);
//
//   void ForEachEntry(
//       std::function<void(const std::string &name, std::shared_ptr<Entry>)>
//       cb) {
//     for (auto &[name, entry] : _entries) {
//       cb(name, entry);
//     }
//   }
//
//   void TraverseTopDown(
//       std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
//     TraverseTopDown({}, cb);
//   }
//
//   void TraverseDownTop(
//       std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
//     TraverseDownTop({}, cb);
//   }
//
//   bool IsEmpty() const { return _entries.empty(); }
//
//   bool Add(const EntryPath &path, std::shared_ptr<Entry> entry) {
//     if (!CanAdd(entry))
//       return false;
//
//     return Add(path, {}, entry);
//   }
//
//   std::shared_ptr<Entry> Remove(const EntryPath &path) {
//     return Remove(path, {});
//   }
//
//   std::shared_ptr<Entry> FindEntry(const EntryPath &path) const override;
//
//   void Serialize(EntryProperties &properties) const override;
//
// protected:
//   virtual bool CanAdd(std::shared_ptr<Entry> entry) = 0;
//   void DeserializeInternal(EntryPath path,
//                            const EntryProperties &properties) override;
//   void CloneFrom(std::shared_ptr<Entry> entry) override;
//
// private:
//   bool Add(const EntryPath &path, EntryPath parent,
//            std::shared_ptr<Entry> entry);
//   std::shared_ptr<Entry> Remove(const EntryPath &path, EntryPath parent);
//   void TraverseTopDown(
//       const EntryPath &parent,
//       std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
//   void TraverseDownTop(
//       const EntryPath &parent,
//       std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
// };
