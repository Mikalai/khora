#include "MoveEntryMessageProcessor.h"

namespace Vandrouka::State::Private::Processors {

void MoveEntryMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::IMoveEntryMessage> cmd,
    Ref<IMessageOutput> sink) {
  if (auto removed = state->GetDir()->Remove(cmd->GetSourcePath()); removed) {
    sink->SubmitAllMessages(removed.Value().Removed);

    if (auto added = state->GetDir()->Add(
            cmd->GetTargetPath().Append(cmd->GetSourcePath().GetLeafName()),
            removed.Value().Removed.back()->GetEntry());
        added) {

      sink->SubmitAllMessages(added.Value().Added);
    } else {
      sink->SubmitError(added.Error());
    }
  } else {
    sink->SubmitError(removed.Error());
  }
}

} // namespace Vandrouka::State::Private
