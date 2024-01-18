#include "BulkOperationStartedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {
void BulkOperationStartedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<IBulkOperationStartedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->_bulkOperation++;
}
} // namespace Vandrouka
