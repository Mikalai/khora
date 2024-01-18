#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"

namespace Vandrouka {

class BulkOperationEndedMessageProcessor
    : public MessageProcessorBase<BulkOperationEndedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IBulkOperationEndedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IBulkOperationEndedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka