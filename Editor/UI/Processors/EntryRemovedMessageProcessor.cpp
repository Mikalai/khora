#include "EntryRemovedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void EntryRemovedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<Catalog::Messages::IEntryRemovedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->RemoveEntry(cmd->GetPath());
}

} // namespace Vandrouka::UI::Private