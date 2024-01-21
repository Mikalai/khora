#include "EntryAddedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void EntryAddedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<Catalog::Messages::IEntryAddedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->AddEntry(cmd->GetPath(), cmd->GetEntry()->GetType());
}

} // namespace Vandrouka::UI::Private
