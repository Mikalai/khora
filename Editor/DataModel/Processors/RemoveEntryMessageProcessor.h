#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class RemoveEntryMessageProcessor
    : public MessageProcessorBase<RemoveEntryMessageProcessor, IDataModelState,
                                  IRemoveEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<IRemoveEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka