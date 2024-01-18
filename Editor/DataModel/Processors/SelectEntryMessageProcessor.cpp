#include "SelectEntryMessageProcessor.h"
#include "../../ISharedEntry.h"
#include "../../Messages/EntrySelectedMessage.h"

namespace Vandrouka {

void Vandrouka::SelectEntryMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<ISelectEntryMessage> cmd,
    Ref<IMessageOutput> sink) {
  if (!state->CanCompile()) {
    return;
  }

  auto entry = state->GetDir()->FindEntry(cmd->GetPath());

  state->SetActiveEntry(entry);

  if (!entry)
    return;

  if (auto shared = entry.Cast<ISharedEntry>(); shared) {
    sink->SubmitMessage(new EntrySelectedMessage{
        shared->CreateShared(state->GetSyncContext())});
  } else {
    sink->SubmitMessage(new EntrySelectedMessage{entry});
  }
}

} // namespace Vandrouka