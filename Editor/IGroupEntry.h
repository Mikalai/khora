#pragma once

#include "IReferenced.h"
#include <vsg/all.h>

namespace Vandrouka {

class IGroupEntry : public IReferenced {
public:
  virtual vsg::ref_ptr<vsg::Group> GetGroup() = 0;
};
template <> struct GetIID<IGroupEntry> {
  static constexpr InterfaceId Id = {{0x9c, 0xc0, 0x54, 0xc0, 0xe2, 0x3f, 0x4d,
                                      0x85, 0x9b, 0x42, 0x5d, 0xab, 0x6b, 0x39,
                                      0xe6, 0xb8}};
};

class GroupEntry;
template <> struct GetCID<GroupEntry> {
  static constexpr InterfaceId Id = {{0x66, 0x13, 0x73, 0x32, 0x78, 0x35, 0x46,
                                      0x20, 0x9a, 0x7d, 0xf6, 0xbd, 0x65, 0xce,
                                      0x9b, 0xe9}};
};

} // namespace Vandrouka
