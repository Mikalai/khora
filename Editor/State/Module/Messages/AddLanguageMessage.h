#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IAddLanguageMessage.h>

namespace Vandrouka {

class AddLanguageMessage
    : public Fundamental::Private::MessageBase<AddLanguageMessage, State::Messages::IAddLanguageMessage> {
public:

  AddLanguageMessage(const std::string &_value) : _value(_value) {}
  std::string GetValue() override { return _value; }

private:
  std::string _value;
};

} // namespace Vandrouka