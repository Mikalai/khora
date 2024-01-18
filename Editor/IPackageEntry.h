#pragma once

#include <vsg/core/Object.h>

#include "IEntry.h"

namespace Vandrouka {

class IPackageEntry : public IReferenced {
public:  
  virtual vsg::ref_ptr<vsg::Object> GetData() const = 0;
  virtual Ref<IPackageEntry> SetData(vsg::ref_ptr<vsg::Object> data) = 0;
};

template <> struct GetIID<IPackageEntry> {
  static constexpr InterfaceId Id = {{0x84, 0x87, 0xe8, 0x5d, 0x6, 0x3, 0x49,
                                      0x10, 0x86, 0x14, 0x73, 0x87, 0xa5, 0xbc,
                                      0x31, 0x9e}};
};

} // namespace Vandrouka
