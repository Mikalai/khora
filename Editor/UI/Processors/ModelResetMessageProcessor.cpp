#include "ModelResetMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void ModelResetMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<IModelResetMessage> cmd,
    Ref<IMessageOutput> sink) {

  state->GetState()->Reset(cmd->GetRoot());

}

} // namespace Vandrouka
