#pragma once

#include "IEntry.h"

namespace Vandrouka {

class ICloneEntry : public IReferenced {
public:
  virtual Ref<IEntry> Clone() const = 0;
};

template <> struct GetIID<ICloneEntry> {
  static constexpr InterfaceId Id = {{0xa, 0xe4, 0xea, 0xbd, 0xde, 0x7a, 0x4d,
                                      0xfb, 0x8c, 0x88, 0x3b, 0x87, 0xfe, 0xeb,
                                      0x19, 0x32}};
};

} // namespace Vandrouka
