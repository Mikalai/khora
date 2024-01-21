#pragma once

#include <Fundamental/Interface/IMessage.h>
#include <string>

namespace Vandrouka::State::Messages {

class IRenameLanguageMessage : public IMessage {
public:
  virtual std::string GetOldValue() = 0;
  virtual std::string GetNewValue() = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IRenameLanguageMessage, 0x54, 0xe1,
            0xa1, 0xe3, 0xb0, 0xbf, 0x48, 0x49, 0xac, 0x57, 0xf7, 0x6, 0x60,
            0x30, 0x9e, 0xa4);
