#include "SetActiveLanguageMessageProcessor.h"
#include "../../Messages/ActiveLanguageChangedMessage.h"

namespace Vandrouka {
void SetActiveLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, const Ref<ISetActiveLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  auto old = cfg->GetActiveLanguage();
  if (cfg->SetActiveLanguage(cmd->GetLanguage())) {
    sink->SubmitMessage(
        new ActiveLanguageChangedMessage{old, cmd->GetLanguage()});
  }
}
} // namespace Vandrouka