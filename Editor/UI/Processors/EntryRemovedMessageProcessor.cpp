#include "EntryRemovedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void EntryRemovedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<IEntryRemovedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->RemoveEntry(cmd->GetPath());
}

} // namespace Vandrouka