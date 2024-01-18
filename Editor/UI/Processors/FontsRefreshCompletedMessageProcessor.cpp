#include "FontsRefreshCompletedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {
void FontsRefreshCompletedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<IFontsRefreshCompletedMessage> cmd, Ref<IMessageOutput> sink) {
  auto s = state->GetState();
  s->_fontsCache = cmd->GetFonts();
  s->UpdateFonts();
}
} // namespace Vandrouka