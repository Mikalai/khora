#include "CopyEntryMessageProcessor.h"
#include "../../ICloneEntry.h"

namespace Vandrouka {

void CopyEntryMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                               Ref<ICopyEntryMessage> cmd,
                                               Ref<IMessageOutput> sink) {
  auto o = state->GetDir()->FindEntry(cmd->GetSourcePath());
  if (!o) {
    sink->SubmitError(NotFoundError(cmd->GetSourcePath().Path));
    return;
  }

  if (auto [c, error] = Cast<ICloneEntry>(o); !error) {
    auto obj = c->Clone();
    assert(obj);
    state->GetDir()->Add(
        cmd->GetTargetPath().Append(cmd->GetSourcePath().GetLeafName()), obj);
  } else {
    sink->SubmitError(error);
  }
}
} // namespace Vandrouka