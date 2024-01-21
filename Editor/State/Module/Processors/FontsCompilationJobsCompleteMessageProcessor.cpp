#include "FontsCompilationJobsCompleteMessageProcessor.h"
#include "CompileSceneProcessor.h"
#include <State/Module/Messages/LanguageAddedMessage.h>
#include <State/Module/Messages/SceneCompeledMessage.h>

namespace Vandrouka::State::Private::Processors {

void FontsCompilationJobsCompleteMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state,
    Ref<State::Messages::IFontsCompilationJobsCompleteMessage> cmd,
    Ref<IMessageOutput> sink) {
  if (auto state = cmd->GetState()) {
    auto root = CompileSceneProcessor::Compile(state->GetRootPath(), state,
                                               state->GetRoot(), sink);
    sink->SubmitMessage(new Messages::SceneCompeledMessage{root});
  }
}

} // namespace Vandrouka::State::Private