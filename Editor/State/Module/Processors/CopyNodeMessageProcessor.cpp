#include "CopyNodeMessageProcessor.h"
#include <Catalog/Interface/IProxyEntry.h>

namespace Vandrouka::State::Private::Processors {

void CopyNodeMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::ICopyNodeMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto entry = state->GetDir()->FindEntry(cmd->GetSourcePath());

  if (!entry) {
    sink->SubmitError(
        CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetSourcePath().Path));
    return;
  }

  auto localPath =
      cmd->GetTargetPath().Path + "/" + cmd->GetSourcePath().GetLeafName();

  if (auto p = entry.Cast<Catalog::ISupportsProxy>(); p) {
    state->GetDir()->Add({localPath}, p->CreateProxy(cmd->GetSourcePath()));
  } else {
    sink->SubmitError(
        CreateError(LOG_NOT_IMPLEMENTED, cmd->GetSourcePath().Path));
  }
}

} // namespace Vandrouka::State::Private::Processors