#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class UnhandledMessageProcessor
    : public MessageProcessorBase<UnhandledMessageProcessor, IDataModelState,
                                  IMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, const Ref<IMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka