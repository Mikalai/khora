#include "LanguageAddedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

    void LanguageAddedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<ILanguageAddedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->AddLanguage(cmd->GetValue());
}

} // namespace Vandrouka