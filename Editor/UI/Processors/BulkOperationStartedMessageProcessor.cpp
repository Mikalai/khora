#include "BulkOperationStartedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void BulkOperationStartedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::IBulkOperationStartedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->_bulkOperation++;
}

} // namespace Vandrouka::UI::Private
