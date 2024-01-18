#include "EntrySelectedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {
void EntrySelectedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<IEntrySelectedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->SelectEntry(cmd->GetSelectedEntry());
}
} // namespace Vandrouka