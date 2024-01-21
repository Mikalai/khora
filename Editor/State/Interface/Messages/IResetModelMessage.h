#pragma once

#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IResetModelMessage : public IMessage {};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IResetModelMessage, 0x14, 0x8, 0xab,
            0x76, 0xa4, 0x53, 0x46, 0x34, 0x80, 0xd1, 0xbc, 0xd, 0xf6, 0xbb,
            0x52, 0x83);
