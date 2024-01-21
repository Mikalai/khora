#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IRemoveLanguageMessage.h>

namespace Vandrouka::State::Private::Messages {

class RemoveLanguageMessage
    : public Fundamental::Private::MessageBase<RemoveLanguageMessage, State::Messages::IRemoveLanguageMessage> {

public:
  RemoveLanguageMessage(const std::string &_value) : _value(_value) {}
  std::string GetValue() override { return _value; }

private:
  std::string _value;
};


} // namespace Vandrouka