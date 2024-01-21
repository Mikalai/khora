#pragma once

#include <string>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IRemoveLanguageMessage : public IMessage {
public:
  virtual std::string GetValue() = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IRemoveLanguageMessage, 0x9b, 0xc2,
            0xa2, 0x55, 0x5c, 0xb1, 0x4c, 0x4e, 0xbd, 0xb7, 0xa, 0x1f, 0xd9,
            0x26, 0xed, 0x15);
