#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class CopyEntryMessageProcessor
    : public MessageProcessorBase<CopyEntryMessageProcessor, IDataModelState,
                                  ICopyEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<ICopyEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka