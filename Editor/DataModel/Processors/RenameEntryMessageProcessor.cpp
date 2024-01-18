#include "RenameEntryMessageProcessor.h"

namespace Vandrouka {

void RenameEntryMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                                 Ref<IRenameEntryMessage> cmd,
                                                 Ref<IMessageOutput> sink) {
  auto oldEntry = state->GetDir()->FindEntry(cmd->GetOldPath());
  if (!oldEntry) {
    sink->SubmitError(new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                                       cmd->GetOldPath().Path));
    return;
  }

  auto newEntry = state->GetDir()->FindEntry(cmd->GetNewPath());
  if (newEntry) {
    sink->SubmitError(new GenericError(
        LOG_LEVEL_ERROR, LOG_ENTRY_ALREADY_EXISTS, cmd->GetNewPath().Path));
    return;
  }

  if (auto removedResult = state->GetDir()->Remove(cmd->GetOldPath());
      removedResult) {

    sink->SubmitAllMessages(removedResult.Value().Removed);

    if (auto addedResult = state->GetDir()->Add(
            cmd->GetNewPath(),
            removedResult.Value().Removed.back()->GetEntry());
        addedResult) {

      sink->SubmitAllMessages(addedResult.Value().Added);

    } else {
      sink->SubmitError(addedResult.Error());
    }

  } else {
    sink->SubmitError(removedResult.Error());
  }
}

} // namespace Vandrouka