#include "LongOperationEndedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void LongOperationEndedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<ILongOperationEndedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->EndOperation(cmd->GetOperation());
}

} // namespace Vandrouka