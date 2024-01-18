#include "EntryAddedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void EntryAddedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<IEntryAddedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->AddEntry(cmd->GetPath(), cmd->GetEntry()->GetType());
}

} // namespace Vandrouka
