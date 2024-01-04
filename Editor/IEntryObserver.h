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

} // namespace Vandrouka

class Entry;

class IEntryObserver {
public:
  virtual ~IEntryObserver() {}

  virtual void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) = 0;
  virtual void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) = 0;
  virtual void OnPropertyChanged(std::shared_ptr<Entry> sender,
                                 std::string_view name) = 0;
  virtual void OnError(const LogNotification &cmd) const = 0;
};
