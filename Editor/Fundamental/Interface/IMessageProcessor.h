#pragma once

#include <Fundamental/Interface/IError.h>
#include <Fundamental/Interface/IMessage.h>
#include <Fundamental/Interface/IMessageOutput.h>
#include <Fundamental/Interface/IReferenced.h>
#include <boost/uuid/uuid_hash.hpp>
#include <span>

namespace Vandrouka::Fundamental {

class IMessageProcessor : public IReferenced {
public:
  virtual std::span<MessageId> GetMessageIds() = 0;
  virtual void Process(Ref<IReferenced> state, Ref<IMessage> msg,
                       Ref<IMessageOutput> sink) = 0;
};

} // namespace Vandrouka::Fundamental

DECLARE_IID(Vandrouka::Fundamental::IMessageProcessor, 0x3b, 0xc2, 0x63, 0xc5,
            0x16, 0x64, 0x42, 0x9, 0x9c, 0x28, 0x1b, 0xe2, 0x38, 0x84, 0xbe,
            0x4f);