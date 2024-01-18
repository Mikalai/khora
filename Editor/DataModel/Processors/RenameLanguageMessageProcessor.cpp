#include "RenameLanguageMessageProcessor.h"
#include "../../Messages/LanguageAddedMessage.h"
#include "../../Messages/LanguageRemovedMessage.h"

namespace Vandrouka {

void RenameLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<IRenameLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  auto langs = cfg->GetLanguages();
  if (auto it = std::find(langs.begin(), langs.end(), cmd->GetOldValue());
      it == langs.end()) {
    sink->SubmitError(new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                                       cmd->GetOldValue()));
    return;
  }

  if (auto it = std::find(langs.begin(), langs.end(), cmd->GetNewValue());
      it != langs.end()) {
    sink->SubmitError(new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                                       cmd->GetNewValue()));
    return;
  }

  cfg->RemoveLanguage(cmd->GetOldValue());
  cfg->AddLanguage(cmd->GetNewValue());

  sink->SubmitMessage(new LanguageRemovedMessage{cmd->GetOldValue()});
  sink->SubmitMessage(new LanguageAddedMessage{cmd->GetNewValue()});
}

} // namespace Vandrouka