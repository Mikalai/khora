#pragma once

#include <boost/uuid/uuid.hpp>
#include <functional>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string_view>
#include <vector>

#include "EntryPath.h"
#include "EntryType.h"
#include "IEntryObserver.h"
#include "IReferenced.h"

class Entry;
class IEntryObserver;
class AsyncQueue;

namespace Vandrouka {

class IEntry;
using EntryRef = Ref<IEntry>;

class IEntry : public IReferenced {
public:
  virtual EntryType GetType() const = 0;
  virtual EntryRef GetParent() const = 0;
  virtual void SetParent(IEntry* parent) = 0;
  virtual EntryRef GetRoot() const = 0;
};

template <> struct GetIID<IEntry> {
  static constexpr InterfaceId Id = {{0x12, 0x98, 0x25, 0x2c, 0x1, 0x45, 0x4e,
                                      0xf3, 0x8a, 0xf8, 0x56, 0xee, 0x9a, 0xf7,
                                      0x11, 0x2d}};
};

} // namespace Vandrouka
