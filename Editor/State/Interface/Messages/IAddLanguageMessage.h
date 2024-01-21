#pragma once

#include <string>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IAddLanguageMessage : public IMessage {
public:
  virtual std::string GetValue() = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IAddLanguageMessage, 0x47, 0x1e, 0x73,
            0x3, 0xeb, 0xeb, 0x48, 0x2, 0x81, 0xe0, 0xb0, 0x8, 0x41, 0x51, 0xc7,
            0xea);
