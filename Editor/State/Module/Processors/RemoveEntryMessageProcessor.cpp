#include "RemoveEntryMessageProcessor.h"

namespace Vandrouka::State::Private::Processors {

void RemoveEntryMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::IRemoveEntryMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetDir()->Remove(cmd->GetPath());
}

} // namespace Vandrouka::State::Private::Processors