#include "LongOperationStartedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void LongOperationStartedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<Fundamental::Messages::ILongOperationStartedMessage> cmd, Ref<IMessageOutput> sink) {
  state->GetState()->BeginOperation(cmd->GetOperation());
}

} // namespace Vandrouka::UI::Private