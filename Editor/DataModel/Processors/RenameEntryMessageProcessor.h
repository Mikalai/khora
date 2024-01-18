#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class RenameEntryMessageProcessor
    : public MessageProcessorBase<RenameEntryMessageProcessor, IDataModelState,
                                  IRenameEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<IRenameEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka