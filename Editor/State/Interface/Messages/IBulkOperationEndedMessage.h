#pragma once

#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IBulkOperationEndedMessage : public IMessage {};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IBulkOperationEndedMessage, 0xc2, 0x57,
            0x31, 0x62, 0x9c, 0xca, 0x41, 0xab, 0xbc, 0xf4, 0x7, 0xee, 0xf0,
            0x9e, 0x3, 0x2f);
