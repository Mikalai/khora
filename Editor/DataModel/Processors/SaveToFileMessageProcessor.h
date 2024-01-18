#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class SaveToFileMessageProcessor
    : public MessageProcessorBase<SaveToFileMessageProcessor, IDataModelState,
                                  ISaveToFileMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<ISaveToFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};


} // namespace Vandrouka