#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {


class BulkOperationStartedMessageProcessor
    : public MessageProcessorBase<BulkOperationStartedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IBulkOperationStartedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IBulkOperationStartedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka