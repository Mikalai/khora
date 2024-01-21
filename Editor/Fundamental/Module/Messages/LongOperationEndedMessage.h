#pragma once

#include <Fundamental/Interface/Messages/ILongOperationEndedMessage.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::Fundamental::Private::Messages {

class LongOperationEndedMessage
    : public Fundamental::Private::MessageBase<
          LongOperationEndedMessage,
          Fundamental::Messages::ILongOperationEndedMessage> {
public:
  LongOperationEndedMessage(LongOperation op) : _op{std::move(op)} {}

  const LongOperation &GetOperation() const override { return _op; }

private:
  LongOperation _op;
};

} // namespace Vandrouka::Fundamental::Private
