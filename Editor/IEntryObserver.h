#pragma once

#include "EntryPath.h"
#include "Errors.h"
#include "IObserver.h"
#include <memory>

namespace Vandrouka {

class IEntry;

class IPropertyChangedMessage : public IMessage {
public:
  virtual Ref<IEntry> GetOwner() const = 0;
  virtual const std::string_view GetProperty() const = 0;
};

template <> struct GetIID<IPropertyChangedMessage> {
  static constexpr InterfaceId Id = {{0x34, 0x3, 0x9c, 0xf, 0x70, 0xd9, 0x47,
                                      0x30, 0xb6, 0x30, 0xd5, 0xce, 0xca, 0x43,
                                      0xbe, 0x57}};
};

class IEntryAddedMessage : public IMessage {
public:
  virtual Ref<IEntry> GetParent() const = 0;
  virtual Ref<IEntry> GetEntry() const = 0;
  virtual EntryPath GetPath() const = 0;
};

template <> struct GetIID<IEntryAddedMessage> {
  static constexpr InterfaceId Id = {{0xf9, 0x81, 0x34, 0x88, 0x98, 0x6, 0x4b,
                                      0x5f, 0xbf, 0xa1, 0x5, 0xb6, 0x81, 0x78,
                                      0xe4, 0xa1}};
};

class IEntryRemovedMessage : public IMessage {
public:
  virtual Ref<IEntry> GetParent() const = 0;
  virtual Ref<IEntry> GetEntry() const = 0;
  virtual EntryPath GetPath() const = 0;
};

template <> struct GetIID<IEntryRemovedMessage> {
  static constexpr InterfaceId Id = {{0xe0, 0x97, 0x50, 0x9, 0x42, 0xd7, 0x47,
                                      0x45, 0xa2, 0xeb, 0xd8, 0x96, 0xa2, 0xf0,
                                      0x8f, 0x54}};
};

} // namespace Vandrouka
//
//class Entry;
//
//class IEntryObserver {
//public:
//  virtual ~IEntryObserver() {}
//
//  virtual void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) = 0;
//  virtual void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) = 0;
//  virtual void OnPropertyChanged(std::shared_ptr<Entry> sender,
//                                 std::string_view name) = 0;
//  virtual void OnError(const LogNotification &cmd) const = 0;
//};
