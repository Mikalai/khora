#pragma once

#include "IReferenced.h"

namespace Vandrouka {

class IAsyncQueue;

class ISharedEntry : public IReferenced {
public:
  virtual EntryRef CreateShared(Ref<IAsyncQueue> queue) = 0;
};

template <> struct GetIID<ISharedEntry> {
  static constexpr InterfaceId Id = {{0x8b, 0xab, 0x6e, 0x19, 0xa4, 0xa5, 0x4c,
                                      0x2e, 0xa5, 0xc4, 0, 0xf8, 0x7b, 0x79,
                                      0xf5, 0x7e}};
};

} // namespace Vandrouka
