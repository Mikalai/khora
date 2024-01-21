#pragma once

#include <string>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ISetActiveLanguageMessage : public IMessage {
public:
  virtual const std::string &GetLanguage() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ISetActiveLanguageMessage, 0x46, 0x38,
            0xdb, 0x7b, 0x2b, 0x62, 0x48, 0xc8, 0xbf, 0xad, 0x9a, 0xfe, 0xd3,
            0x10, 0x62, 0xb2);
