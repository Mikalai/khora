#include "SetActiveLanguageMessageProcessor.h"
#include <State/Module/Messages/ActiveLanguageChangedMessage.h>

namespace Vandrouka::State::Private::Processors {

void SetActiveLanguageMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state,
    const Ref<State::Messages::ISetActiveLanguageMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto cfg = state->GetConfig();
  auto old = cfg->GetActiveLanguage();
  if (cfg->SetActiveLanguage(cmd->GetLanguage())) {
    sink->SubmitMessage(
        new Messages::ActiveLanguageChangedMessage{old, cmd->GetLanguage()});
  }
}

} // namespace Vandrouka::State::Private::Processors