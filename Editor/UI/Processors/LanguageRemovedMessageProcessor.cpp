#include "LanguageRemovedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void LanguageRemovedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::ILanguageRemovedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->RemoveLanguage(cmd->GetValue());
}

} // namespace Vandrouka::UI::Private::Processors