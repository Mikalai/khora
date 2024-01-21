#include "FontsRefreshCompletedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void FontsRefreshCompletedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<Fonts::Messages::IFontsRefreshCompletedMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto s = state->GetState();
  s->_fontsCache = cmd->GetFonts();
  s->UpdateFonts();
}

} // namespace Vandrouka::UI::Private