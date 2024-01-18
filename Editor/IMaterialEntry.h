#pragma once

#include <vsg/all.h>

#include "Result.h"

namespace Vandrouka {
class IMaterialEntry : public IReferenced {
public:
  virtual Result<vsg::ref_ptr<vsg::StateGroup>> GetState() const = 0;
};

template <> struct GetIID<IMaterialEntry> {
  static constexpr InterfaceId Id = {{0x4c, 0x9, 0x3d, 0x8, 0x11, 0xd8, 0x44,
                                      0x31, 0xa0, 0xeb, 0x71, 0xa0, 0x59, 0x33,
                                      0xaa, 0xf9}};
};

class MaterialProxyEntry;

template <> struct GetCID<MaterialProxyEntry> {
  static constexpr ClassId Id = {{0x99, 0x8, 0x37, 0x4b, 0x85, 0x14, 0x40, 0x57,
                                  0x85, 0x2d, 0xd1, 0xda, 0xd0, 0, 0x98, 0x85}};
};

class MaterialPackageEntry;

template <> struct GetCID<MaterialPackageEntry> {
  static constexpr ClassId Id = {{0x7c, 0x8, 0x66, 0x65, 0xca, 0xb0, 0x48, 0xeb,
                                  0x85, 0x97, 0x5d, 0xa9, 0xe1, 0x75, 0x1a,
                                  0x45}};
};

} // namespace Vandrouka
