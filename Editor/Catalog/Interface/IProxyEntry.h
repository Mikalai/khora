#pragma once

#include "IEntry.h"

namespace Vandrouka::Catalog {

class IProxyEntry : public Fundamental::IReferenced {
public:
  virtual void SetPath(EntryPath path) = 0;
  virtual EntryPath GetPath() const = 0;
};

class ISupportsProxy : public Fundamental::IReferenced {
public:
  virtual Ref<IEntry> CreateProxy(EntryPath path) = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::IProxyEntry, 0x6b, 0x59, 0x1e, 0xe7, 0x90, 0x67,
            0x4c, 0x57, 0x93, 0xd9, 0x56, 0x16, 0x71, 0x19, 0xb6, 0xa4);

DECLARE_IID(Vandrouka::Catalog::ISupportsProxy, 0x73, 0x12, 0x5f, 0xb5, 0x3a,
            0xa4, 0x48, 0xef, 0xb0, 0x9e, 0xb9, 0x5b, 0xbd, 0xaf, 0x60, 0x1d);