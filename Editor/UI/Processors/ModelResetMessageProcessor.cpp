#include "ModelResetMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void ModelResetMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::IModelResetMessage> cmd, Ref<IMessageOutput> sink) {

  state->GetState()->Reset(cmd->GetRoot());
}

} // namespace Vandrouka::UI::Private
