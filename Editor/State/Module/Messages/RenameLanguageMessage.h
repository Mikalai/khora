#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IRenameLanguageMessage.h>

namespace Vandrouka::State::Private::Messages {

class RenameLanguageMessage
    : public Fundamental::Private::MessageBase<
          RenameLanguageMessage, State::Messages::IRenameLanguageMessage> {
public:
  RenameLanguageMessage(const std::string &_oldValue,
                        const std::string &_newValue)
      : _oldValue(_oldValue), _newValue(_newValue) {}

  std::string GetOldValue() override { return _oldValue; }
  std::string GetNewValue() override { return _newValue; }

private:
  std::string _oldValue;
  std::string _newValue;
};

} // namespace Vandrouka