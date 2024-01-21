#include "LongOperationEndedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void LongOperationEndedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<Fundamental::Messages::ILongOperationEndedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->EndOperation(cmd->GetOperation());
}

} // namespace Vandrouka::UI::Private