#include "SelectEntryMessageProcessor.h"
#include <Catalog/Interface/ISharedEntry.h>
#include <State/Module/Messages/EntrySelectedMessage.h>

namespace Vandrouka::State::Private::Processors {

void SelectEntryMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::ISelectEntryMessage> cmd,
    Ref<IMessageOutput> sink) {
  if (!state->CanCompile()) {
    return;
  }

  auto entry = state->GetDir()->FindEntry(cmd->GetPath());

  state->SetActiveEntry(entry);

  if (!entry)
    return;

  if (auto shared = entry.Cast<Catalog::ISharedEntry>(); shared) {
    sink->SubmitMessage(new Messages::EntrySelectedMessage{
        shared->CreateShared(state->GetSyncContext())});
  } else {
    sink->SubmitMessage(new Messages::EntrySelectedMessage{entry});
  }
}

} // namespace Vandrouka::State::Private::Processors
