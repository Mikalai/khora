#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IResetModelMessage.h>

namespace Vandrouka::State::Private::Messages {

class ResetModelMessage
    : public Fundamental::Private::MessageBase<ResetModelMessage, State::Messages::IResetModelMessage> {};

} // namespace Vandrouka