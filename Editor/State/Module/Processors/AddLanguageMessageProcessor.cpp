#include "AddLanguageMessageProcessor.h"
#include <State/Module/Messages/LanguageAddedMessage.h>

namespace Vandrouka::State::Private::Processors {

void AddLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::IAddLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  if (!cfg->AddLanguage(cmd->GetValue())) {
    sink->SubmitError(CreateError(LOG_ENTRY_ALREADY_EXISTS, cmd->GetValue()));
    return;
  }

  sink->SubmitMessage(new Messages::LanguageAddedMessage{cmd->GetValue()});
}

} // namespace Vandrouka::State::Private