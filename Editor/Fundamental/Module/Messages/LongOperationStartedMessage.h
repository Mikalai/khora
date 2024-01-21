#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <Fundamental/Interface/Messages/ILongOperationStartedMessage.h>

namespace Vandrouka::Fundamental::Private::Messages {

class LongOperationStartedMessage
    : public Fundamental::Private::MessageBase<LongOperationStartedMessage,
                         Fundamental::Messages::ILongOperationStartedMessage> {
public:
  LongOperationStartedMessage(LongOperation op) : _op{std::move(op)} {}

  const LongOperation &GetOperation() const override { return _op; }

private:
  LongOperation _op;
};

} // namespace Vandrouka::Fundamental::Private