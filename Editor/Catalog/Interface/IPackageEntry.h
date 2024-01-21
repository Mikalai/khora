#pragma once

#include <vsg/core/Object.h>

#include <Catalog/Interface/IEntry.h>

namespace Vandrouka::Catalog {

class IPackageEntry : public Fundamental::IReferenced {
public:
  virtual vsg::ref_ptr<vsg::Object> GetData() const = 0;
  virtual Ref<IPackageEntry> SetData(vsg::ref_ptr<vsg::Object> data) = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::IPackageEntry, 0x84, 0x87, 0xe8, 0x5d, 0x6, 0x3,
            0x49, 0x10, 0x86, 0x14, 0x73, 0x87, 0xa5, 0xbc, 0x31, 0x9e);