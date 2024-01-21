#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IActiveLanguageChangedMessage.h>

namespace Vandrouka::State::Private::Messages {

class ActiveLanguageChangedMessage
    : public Fundamental::Private::MessageBase<
          ActiveLanguageChangedMessage,
          State::Messages::IActiveLanguageChangedMessage> {
public:
  ActiveLanguageChangedMessage(std::string oldLanguage, std::string newLanguage)
      : _oldLanguage{oldLanguage}, _newLanguage{newLanguage} {}

  const std::string &GetOldLanguage() const override { return _oldLanguage; }
  const std::string &GetNewLanguage() const override { return _newLanguage; }

private:
  std::string _oldLanguage;
  std::string _newLanguage;
};

} // namespace Vandrouka::State::Private::Messages