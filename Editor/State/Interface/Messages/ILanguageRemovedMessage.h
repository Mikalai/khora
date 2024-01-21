#pragma once

#include <string>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ILanguageRemovedMessage : public IMessage {
public:
  virtual const std::string &GetValue() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ILanguageRemovedMessage, 0xf0, 0xcc,
            0xb0, 0xc, 0x6c, 0x9e, 0x41, 0x63, 0x9f, 0x90, 0xd9, 0x12, 0x68,
            0xe1, 0x46, 0x88);
