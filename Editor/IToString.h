#pragma once

#include "IReferenced.h"
#include <string>

namespace Vandrouka {

class IToString : public IReferenced {
public:
  virtual std::string ToString() const = 0;
};

template <> struct GetIID<IToString> {
  static constexpr InterfaceId Id = {{0xdb, 0x1d, 0xe1, 0x7f, 0x92, 0x92, 0x4d,
                                      0x2f, 0xba, 0x9d, 0x5f, 0x8f, 0x5a, 0xf1,
                                      0x85, 0xdc}};
};

inline std::string ToString(Ref<IReferenced> v) {
  if (auto s = v.Cast<IToString>(); s) {
    return s->ToString();
  }
  return {};
}

} // namespace Vandrouka