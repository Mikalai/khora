#pragma once

#include <Fundamental/Interface/IMessageProcessor.h>

namespace Vandrouka::Fundamental {

class IAggregatedProcessor : public IMessageProcessor {
public:
  virtual void AddProcessor(Ref<IMessageProcessor> processor) = 0;
  virtual void SetUnhandledProcessor(Ref<IMessageProcessor> processor) = 0;
};

} // namespace Vandrouka::Fundamental

DECLARE_IID(::Vandrouka::Fundamental::IAggregatedProcessor, 0x3e, 0x14, 0x3, 0xdb,
            0x8e, 0xbc, 0x44, 0x61, 0x9f, 0x6, 0x7e, 0x91, 0xc4, 0x88, 0x3,
            0xd1);
