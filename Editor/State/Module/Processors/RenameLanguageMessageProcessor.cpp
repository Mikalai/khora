#include "RenameLanguageMessageProcessor.h"
#include <State/Module/Messages/LanguageAddedMessage.h>
#include <State/Module/Messages/LanguageRemovedMessage.h>

namespace Vandrouka::State::Private::Processors {

void RenameLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state,
    Ref<State::Messages::IRenameLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  auto langs = cfg->GetLanguages();
  if (auto it = std::find(langs.begin(), langs.end(), cmd->GetOldValue());
      it == langs.end()) {
    sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetOldValue()));
    return;
  }

  if (auto it = std::find(langs.begin(), langs.end(), cmd->GetNewValue());
      it != langs.end()) {
    sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetNewValue()));
    return;
  }

  cfg->RemoveLanguage(cmd->GetOldValue());
  cfg->AddLanguage(cmd->GetNewValue());

  sink->SubmitMessage(new Messages::LanguageRemovedMessage{cmd->GetOldValue()});
  sink->SubmitMessage(new Messages::LanguageAddedMessage{cmd->GetNewValue()});
}

} // namespace Vandrouka::State::Private::Processors