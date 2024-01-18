#include "ActiveLanguageChangedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void ActiveLanguageChangedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<IActiveLanguageChangedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->SetLanguageActive(cmd->GetOldLanguage(),
                                       cmd->GetNewLanguage());
}

} // namespace Vandrouka