#include "CopyNodeMessageProcessor.h"
#include "../../IProxyEntry.h"

namespace Vandrouka {

void CopyNodeMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<ICopyNodeMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto entry = state->GetDir()->FindEntry(cmd->GetSourcePath());

  if (!entry) {
    sink->SubmitError(NotFoundError(cmd->GetSourcePath().Path));
    return;
  }

  auto localPath =
      cmd->GetTargetPath().Path + "/" + cmd->GetSourcePath().GetLeafName();

  if (auto [p, error] = Cast<ISupportsProxy>(entry); !error) {
    state->GetDir()->Add({localPath}, p->CreateProxy(cmd->GetSourcePath()));
  } else {
    sink->SubmitError(error);
  }
}
} // namespace Vandrouka