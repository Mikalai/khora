#include "ExportToFileMessageProcessor.h"
#include "../CompilationState.h"
#include "CompileSceneProcessor.h"

namespace Vandrouka::State::Private::Processors {

void ExportToFileMessageProcessor::ProcessMessage(
    Ref<IDataModelState> s, Ref<State::Messages::IExportToFileMessage> cmd,
    Ref<IMessageOutput> sink) {

  if (!s->CanCompile()) {
    sink->SubmitError(CreateError(LOG_ENTRY_BUSY, cmd->GetPath()));
    return;
  }

  Ref<ICompilationState> state{new CompilationState()};

  state->SetShowTransforms(false);
  state->SetTransformProxy({});
  state->SetActiveCursor({});
  state->SetActiveEntry({});
  state->SetRootPath({ROOT_SCENE});
  state->SetRoot(s->GetDir()->FindEntry(state->GetRootPath()));

  const auto root = CompileSceneProcessor::Compile(state->GetRootPath(), state,
                                                   state->GetRoot(), sink);

  if (!root) {
    sink->SubmitError(CreateError(LOG_ENTRY_COMPILATION_FAILED, ROOT_SCENE));
    return;
  }

  vsg::write(root, cmd->GetPath());
}
} // namespace Vandrouka::State::Private::Processors