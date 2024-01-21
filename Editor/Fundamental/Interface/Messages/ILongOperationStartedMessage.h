#pragma once

#include <Fundamental/Interface/IMessage.h>
#include <Fundamental/Interface/LongOperation.h>

namespace Vandrouka::Fundamental::Messages {

class ILongOperationStartedMessage : public IMessage {
public:
  virtual const LongOperation &GetOperation() const = 0;
};

} // namespace Vandrouka::Fundamental::Messages

DECLARE_IID(Vandrouka::Fundamental::Messages::ILongOperationStartedMessage,
            0x3c, 0x1d, 0xed, 0x37, 0xe2, 0x29, 0x49, 0xd2, 0xa7, 0xcf, 0xa,
            0x66, 0x39, 0x38, 0xd9, 0xe5);
