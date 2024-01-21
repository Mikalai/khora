#include "FontCompiledMessageProcessor.h"
#include <State/Module/Messages/FontsCompilationJobsCompleteMessage.h>

namespace Vandrouka::State::Private::Processors {

void FontCompiledMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<Fonts::Messages::IFontCompiledMessage> cmd,
    Ref<IMessageOutput> sink) {
  if (auto s = cmd->GetState().Cast<ICompilationState>(); s) {
    s->DecreaseFontCompilationJobs();
    s->AddFont(cmd->GetDisplayName(), cmd->GetFont());
    if (!s->HasFontCompilationJobs()) {
      state->Execute(new Messages::FontsCompilationJobsCompleteMessage{s});
    }
  }
}

} // namespace Vandrouka::State::Private::Data::Processors