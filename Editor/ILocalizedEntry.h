#pragma once

#include "IReferenced.h"
#include <vsg/all.h>

namespace Vandrouka {

class ILocalizedEntry : public IReferenced {
public:  
};

template <> struct GetIID<ILocalizedEntry> {
  static constexpr InterfaceId Id = {{0x3b, 0x19, 0xed, 0x97, 0xcb, 0xe8, 0x4d,
                                      0xca, 0x92, 0, 0xc5, 0x39, 0xd2, 0x1e,
                                      0x35, 0x11}};
};

class LocalizedEntry;

template <> struct GetCID<LocalizedEntry> {
  static constexpr InterfaceId Id = {{0x60, 0xec, 0x7d, 0x5f, 0x3b, 0x10, 0x40,
                                      0xa6, 0xb5, 0x5e, 0xac, 0xe3, 0x8f, 0x8b,
                                      0x10, 0x7d}};
};

} // namespace Vandrouka