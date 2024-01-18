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

class GeometryProxyEntry;

template <> struct GetCID<GeometryProxyEntry> {
  static constexpr ClassId Id = {{0xd5, 0x84, 0x1f, 0xc, 0x7, 0xc4, 0x47, 0xe1,
                                  0x94, 0x5a, 0x36, 0x83, 0x50, 0x85, 0x4a,
                                  0xd6}};
};

class GeometryPackageEntry;

template <> struct GetCID<GeometryPackageEntry> {
  static constexpr ClassId Id = {{0xb2, 0xd1, 0x37, 0xaa, 0xee, 0x63, 0x40,
                                  0xe4, 0x85, 0x8f, 0, 0x1c, 0x20, 0xb, 0x27,
                                  0x99}};
};

} // namespace Vandrouka
