#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ISetActiveLanguageMessage.h>

namespace Vandrouka::State::Private::Messages {

class SetActiveLanguageMessage
    : public Fundamental::Private::MessageBase<SetActiveLanguageMessage, State::Messages::ISetActiveLanguageMessage> {
public:
  SetActiveLanguageMessage(const std::string &_value) : _value(_value) {}

  const std::string &GetLanguage() const override { return _value; }

private:
  std::string _value;
};

} // namespace Vandrouka