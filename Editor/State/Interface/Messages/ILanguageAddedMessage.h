#pragma once

#include <string>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ILanguageAddedMessage : public IMessage {
public:
  virtual const std::string &GetValue() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ILanguageAddedMessage, 0x67, 0x41, 0x4b,
            0x9f, 0x40, 0xdb, 0x49, 0x30, 0xb7, 0xf5, 0xf8, 0x18, 0x2f, 0xb6,
            0x4b, 0x9c);
