#pragma once

#include "EntryPath.h"
#include "IEntry.h"
#include "IObserver.h"
#include <functional>

namespace Vandrouka {

class DirectoryChanges {
public:
  std::vector<Ref<IEntryAddedMessage>> Added;
  std::vector<Ref<IEntryRemovedMessage>> Removed;
};

class IDirectoryEntry : public IEntry {
public:
  virtual void
  ForEachEntry(std::function<void(const std::string &name, EntryRef)> cb) = 0;
  virtual void TraverseTopDown(std::function<void(EntryPath path, EntryRef)> cb,
                               const EntryPath &parent = {}) = 0;
  virtual void TraverseDownTop(std::function<void(EntryPath path, EntryRef)> cb,
                               const EntryPath &parent = {}) = 0;
  virtual bool IsEmpty() const = 0;
  virtual bool CanAdd(EntryRef ref) = 0;
  virtual Result<DirectoryChanges> Add(const EntryPath &path, EntryRef entry) = 0;
  virtual Result<DirectoryChanges> Remove(const EntryPath &path) = 0;
  virtual EntryRef FindEntry(const EntryPath &path) const = 0;
};

template <> struct GetIID<IDirectoryEntry> {
  static constexpr InterfaceId Id = {{0x8b, 0x60, 0x9, 0xae, 0xa6, 0xcc, 0x4c,
                                      0x8d, 0xaf, 0xcd, 0xec, 0x35, 0xd3, 0xe,
                                      0xe6, 0xa6}};
};
} // namespace Vandrouka
