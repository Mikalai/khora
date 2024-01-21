#pragma once

#include <Fundamental/Interface/IMessage.h>
#include <Fundamental/Interface/LongOperation.h>

namespace Vandrouka::Fundamental::Messages {

class ILongOperationEndedMessage : public IMessage {
public:
  virtual const LongOperation &GetOperation() const = 0;
};

} // namespace Vandrouka::Fundamental::Messages

DECLARE_IID(Vandrouka::Fundamental::Messages::ILongOperationEndedMessage, 0xc9,
            0xfc, 0x4e, 0x1f, 0xe2, 0xe, 0x4d, 0x74, 0xa5, 0xa4, 0x96, 0x40,
            0x89, 0xa, 0x4c, 0x6d);
