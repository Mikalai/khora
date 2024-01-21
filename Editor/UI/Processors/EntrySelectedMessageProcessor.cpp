#include "EntrySelectedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void EntrySelectedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::IEntrySelectedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->SelectEntry(cmd->GetSelectedEntry());
}

} // namespace Vandrouka::UI::Private