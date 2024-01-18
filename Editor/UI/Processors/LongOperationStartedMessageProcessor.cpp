#include "LongOperationStartedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void LongOperationStartedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<ILongOperationStartedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->BeginOperation(cmd->GetOperation());
}

} // namespace Vandrouka