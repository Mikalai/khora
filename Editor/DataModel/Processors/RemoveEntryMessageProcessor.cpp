#include "RemoveEntryMessageProcessor.h"

namespace Vandrouka {

void RemoveEntryMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                                 Ref<IRemoveEntryMessage> cmd,
                                                 Ref<IMessageOutput> sink) {
  state->GetDir()->Remove(cmd->GetPath());
}

} // namespace Vandrouka