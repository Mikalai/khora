#include "RemoveLanguageMessageProcessor.h"
#include <State/Module/Messages/LanguageRemovedMessage.h>

namespace Vandrouka::State::Private::Processors {

void RemoveLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state,
    Ref<State::Messages::IRemoveLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  if (!cfg->RemoveLanguage(cmd->GetValue())) {
    sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetValue()));
    return;
  }

  sink->SubmitMessage(new Messages::LanguageRemovedMessage{cmd->GetValue()});
}

} // namespace Vandrouka::State::Private