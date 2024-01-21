#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ILanguageRemovedMessage.h>

namespace Vandrouka::State::Private::Messages {

class LanguageRemovedMessage
    : public Fundamental::Private::MessageBase<LanguageRemovedMessage, State::Messages::ILanguageRemovedMessage> {
public:
  LanguageRemovedMessage(std::string value) : _value{value} {}
  const std::string &GetValue() const override { return _value; }

private:
  std::string _value;
};

} // namespace Vandrouka