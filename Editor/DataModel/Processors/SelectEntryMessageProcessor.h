#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class SelectEntryMessageProcessor
    : public MessageProcessorBase<SelectEntryMessageProcessor, IDataModelState,
                                  ISelectEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<ISelectEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};
} // namespace Vandrouka