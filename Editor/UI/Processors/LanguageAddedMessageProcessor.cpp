#include "LanguageAddedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void LanguageAddedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::ILanguageAddedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->AddLanguage(cmd->GetValue());
}

} // namespace Vandrouka::UI::Private::Processors
