#pragma once

#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IBulkOperationStartedMessage : public IMessage {};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IBulkOperationStartedMessage, 0xce, 0x4,
            0x16, 0xe, 0x82, 0xe6, 0x48, 0xd1, 0x99, 0x2c, 0xb8, 0xb5, 0x51,
            0x63, 0x4d, 0x72);
