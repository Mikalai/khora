#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class RequestSuggestedChildrenMessageProcessor
    : public MessageProcessorBase<RequestSuggestedChildrenMessageProcessor,
                                  IDataModelState,
                                  IRequestSuggestedChildrenMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<IRequestSuggestedChildrenMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka