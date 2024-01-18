#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class ResetModelMessageProcessor
    : public MessageProcessorBase<ResetModelMessageProcessor, IDataModelState,
                                  IResetModelMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<IResetModelMessage> cmd,
                      Ref<IMessageOutput> sink);
};
} // namespace Vandrouka