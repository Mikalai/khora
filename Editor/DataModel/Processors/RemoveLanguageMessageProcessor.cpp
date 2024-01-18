#include "RemoveLanguageMessageProcessor.h"
#include "../../Messages/LanguageRemovedMessage.h"

namespace Vandrouka {

void RemoveLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<IRemoveLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  if (!cfg->RemoveLanguage(cmd->GetValue())) {
    sink->SubmitError(new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                                       cmd->GetValue()));
    return;
  }

  sink->SubmitMessage(new LanguageRemovedMessage{cmd->GetValue()});
}

} // namespace Vandrouka