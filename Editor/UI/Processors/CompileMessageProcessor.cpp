#include "CompileMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {
void CompileMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<ICompileMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto s = state->GetState();
  auto result =
      s->viewerWindow->viewer->compileManager->compile(cmd->GetResultObject());
  cmd->GetCompletion()->Execute();
}
} // namespace Vandrouka