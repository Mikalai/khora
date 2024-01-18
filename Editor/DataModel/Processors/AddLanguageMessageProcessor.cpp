#include "AddLanguageMessageProcessor.h"
#include "../../Messages/LanguageAddedMessage.h"

namespace Vandrouka {

void AddLanguageMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                                 Ref<IAddLanguageMessage> cmd,
                                                 Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  if (!cfg->AddLanguage(cmd->GetValue())) {
    sink->SubmitError(new GenericError(
        LOG_LEVEL_ERROR, LOG_ENTRY_ALREADY_EXISTS, cmd->GetValue()));
    return;
  }

  sink->SubmitMessage(new LanguageAddedMessage{cmd->GetValue()});
}

} // namespace Vandrouka