#include "CompileMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void CompileMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::ICompileMessage> cmd, Ref<IMessageOutput> sink) {
  auto s = state->GetState();
  auto result =
      s->viewerWindow->viewer->compileManager->compile(cmd->GetResultObject());
  cmd->GetCompletion()->Execute();
}

} // namespace Vandrouka::UI::Private::Processors