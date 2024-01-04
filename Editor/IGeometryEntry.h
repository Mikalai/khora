#pragma once

#include "Entry.h"
#include "IReferenced.h"
#include <vsg/all.h>

namespace Vandrouka {
class IGeometryEntry : public IReferenced {
public:
  virtual vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() = 0;
};

template <> struct GetIID<IGeometryEntry> {
  static constexpr InterfaceId Id = {{0xc2, 0x38, 0x99, 0x4c, 0x89, 0xf7, 0x46,
                                      0xc0, 0x96, 0xde, 0xe8, 0xc3, 0x8d, 0x37,
                                      0x7c, 0x71}};
};

} // namespace Vandrouka
