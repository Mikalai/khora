#pragma once

#include "EntryPath.h"
#include "IEntry.h"
#include "IObserver.h"
#include <functional>

namespace Vandrouka {

class IEntryAddedMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
  virtual EntryRef GetEntry() const = 0;
};
template <> struct GetIID<IEntryAddedMessage> {
  static constexpr InterfaceId Id = {{0x25, 0x2b, 0x63, 0x19, 0x65, 0x64, 0x43,
                                      0xe8, 0xa7, 0xff, 0xf, 0x2d, 0x51, 0x83,
                                      0x7a, 0xba}};
};

class IEntryRemovedMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
  virtual EntryRef GetEntry() const = 0;
};
template <> struct GetIID<IEntryRemovedMessage> {
  static constexpr InterfaceId Id = {{0x31, 0x4b, 0xcf, 0x5e, 0, 0x9f, 0x40,
                                      0xfd, 0x82, 0x6, 0xc2, 0xad, 0x32, 0x5c,
                                      0x1d, 0x6a}};
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
  virtual bool Add(const EntryPath &path, EntryRef entry,
                   const EntryPath &parent = {}) = 0;
  virtual EntryRef Remove(const EntryPath &path,
                          const EntryPath &parent = {}) = 0;
  virtual EntryRef FindEntry(const EntryPath &path) const = 0;
};

template <> struct GetIID<IDirectoryEntry> {
  static constexpr InterfaceId Id = {{0x8b, 0x60, 0x9, 0xae, 0xa6, 0xcc, 0x4c,
                                      0x8d, 0xaf, 0xcd, 0xec, 0x35, 0xd3, 0xe,
                                      0xe6, 0xa6}};
};
} // namespace Vandrouka
