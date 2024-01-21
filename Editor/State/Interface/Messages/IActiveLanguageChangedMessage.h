#pragma once

#include <Fundamental/Interface/IMessage.h>
#include <string>

namespace Vandrouka::State::Messages {

class IActiveLanguageChangedMessage : public IMessage {
public:
  virtual const std::string &GetOldLanguage() const = 0;
  virtual const std::string &GetNewLanguage() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IActiveLanguageChangedMessage, 0xd0,
            0x77, 0x6e, 0x7e, 0x3c, 0x1d, 0x4d, 0x73, 0xac, 0x14, 0x3d, 0xf0,
            0x23, 0xfc, 0x35, 0xb8);
