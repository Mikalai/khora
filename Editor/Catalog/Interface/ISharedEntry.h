#pragma once

#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Interface/IAsyncQueue.h>

namespace Vandrouka::Catalog {

class ISharedEntry : public Fundamental::IReferenced {
public:
  virtual EntryRef CreateShared(Ref<IAsyncQueue> queue) = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::ISharedEntry, 0x8b, 0xab, 0x6e, 0x19, 0xa4,
            0xa5, 0x4c, 0x2e, 0xa5, 0xc4, 0, 0xf8, 0x7b, 0x79, 0xf5, 0x7e);
