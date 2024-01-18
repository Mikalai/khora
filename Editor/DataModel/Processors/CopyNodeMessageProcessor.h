#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class CopyNodeMessageProcessor
    : public MessageProcessorBase<CopyNodeMessageProcessor, IDataModelState,
                                  ICopyNodeMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<ICopyNodeMessage> cmd,
                      Ref<IMessageOutput> sink);
};
} // namespace Vandrouka