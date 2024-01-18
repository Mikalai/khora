#include "FontsCompilationJobsCompleteMessageProcessor.h"
#include "CompileSceneProcessor.h"
#include "../../Messages/LanguageAddedMessage.h"
#include "../../Messages/SceneCompeledMessage.h"

namespace Vandrouka {

void FontsCompilationJobsCompleteMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<IFontsCompilationJobsCompleteMessage> cmd,
                                                 Ref<IMessageOutput> sink) {
  if (auto state = cmd->GetState()) {
    auto root = CompileSceneProcessor::Compile(state->GetRootPath(), state,
                                   state->GetRoot(), sink);
    sink->SubmitMessage(new SceneCompeledMessage{root});
  }
}

} // namespace Vandrouka