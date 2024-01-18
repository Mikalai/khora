#include "FontCompiledMessageProcessor.h"
#include "../../Messages/CompileSceneMessage.h"
#include "../../Messages/LanguageAddedMessage.h"
#include "../ICompilationState.h"

namespace Vandrouka::Data::Processors {

void FontCompiledMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                                  Ref<IFontCompiledMessage> cmd,
                                                  Ref<IMessageOutput> sink) {
  if (auto s = cmd->GetState().Cast<ICompilationState>(); s) {
    s->DecreaseFontCompilationJobs();
    s->AddFont(cmd->GetDisplayName(), cmd->GetFont());
    if (!s->HasFontCompilationJobs()) {
      state->Execute(new FontsCompilationJobsCompleteMessage{s});
    }
  }
}

} // namespace Vandrouka