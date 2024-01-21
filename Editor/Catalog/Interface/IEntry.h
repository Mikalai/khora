#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Catalog/Interface/EntryType.h>
#include <Fundamental/Interface/IReferenced.h>

namespace Vandrouka::Catalog {

class IEntry;
using EntryRef = Ref<IEntry>;

class IEntry : public Fundamental::IReferenced {
public:
  virtual EntryType GetType() const = 0;
  virtual EntryRef GetParent() const = 0;
  virtual void SetParent(IEntry *parent) = 0;
  virtual EntryRef GetRoot() const = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::IEntry, 0x12, 0x98, 0x25, 0x2c, 0x1, 0x45, 0x4e,
            0xf3, 0x8a, 0xf8, 0x56, 0xee, 0x9a, 0xf7, 0x11, 0x2d);
