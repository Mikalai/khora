#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class MoveEntryMessageProcessor
    : public MessageProcessorBase<MoveEntryMessageProcessor, IDataModelState,
                                  IMoveEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<IMoveEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka