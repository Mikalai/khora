#pragma once

#include <vsg/all.h>

#include "IReferenced.h"

namespace Vandrouka {
class IMaterialEntry : public IReferenced {
public:
  virtual vsg::ref_ptr<vsg::StateGroup> GetState() const = 0;
};

template <> struct GetIID<IMaterialEntry> {
  static constexpr InterfaceId Id = {{0x4c, 0x9, 0x3d, 0x8, 0x11, 0xd8, 0x44,
                                      0x31, 0xa0, 0xeb, 0x71, 0xa0, 0x59, 0x33,
                                      0xaa, 0xf9}};
};

} // namespace Vandrouka
