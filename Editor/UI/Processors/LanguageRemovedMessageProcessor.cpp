#include "LanguageRemovedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

    void LanguageRemovedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<ILanguageRemovedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->RemoveLanguage(cmd->GetValue());
}

} // namespace Vandrouka