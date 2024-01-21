#include "CopyEntryMessageProcessor.h"
#include <Catalog/Interface/ICloneEntry.h>

namespace Vandrouka::State::Private::Processors {

void CopyEntryMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::ICopyEntryMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto o = state->GetDir()->FindEntry(cmd->GetSourcePath());
  if (!o) {
    sink->SubmitError(
        CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetSourcePath().Path));
    return;
  }

  if (auto c = o.Cast<Catalog::ICloneEntry>(); c) {
    auto obj = c->Clone();
    assert(obj);
    state->GetDir()->Add(
        cmd->GetTargetPath().Append(cmd->GetSourcePath().GetLeafName()), obj);
  } else {
    sink->SubmitError(
        CreateError(LOG_NOT_IMPLEMENTED, cmd->GetSourcePath().Path));
  }
}

} // namespace Vandrouka::State::Private