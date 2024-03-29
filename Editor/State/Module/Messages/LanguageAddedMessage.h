#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ILanguageAddedMessage.h>

namespace Vandrouka::State::Private::Messages {

class LanguageAddedMessage
    : public Fundamental::Private::MessageBase<LanguageAddedMessage, State::Messages::ILanguageAddedMessage> {
public:
  LanguageAddedMessage(std::string value) : _value{value} {}
  const std::string &GetValue() const override { return _value; }

  const MessageId &GetTypeID() const override {
    static MessageId id{{0xc4, 0xb, 0xa3, 0x21, 0x2, 0x71, 0x4c, 0xf0, 0xac,
                         0x8b, 0xaf, 0x1, 0xd9, 0xb7, 0xec, 0x46}};
    return id;
  }

private:
  std::string _value;
};

} // namespace Vandrouka