#include "ActiveLanguageChangedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void ActiveLanguageChangedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::IActiveLanguageChangedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->SetLanguageActive(cmd->GetOldLanguage(),
                                       cmd->GetNewLanguage());
}

} // namespace Vandrouka::UI::Private