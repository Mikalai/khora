#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class CreateNodeMessageProcessor
    : public MessageProcessorBase<CreateNodeMessageProcessor, IDataModelState,
                                  ICreateNodeMessage> {

public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<ICreateNodeMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka