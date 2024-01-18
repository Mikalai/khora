#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"
#include "../../LongOperationNotification.h"

namespace Vandrouka {


class LongOperationStartedMessageProcessor
    : public MessageProcessorBase<LongOperationStartedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ILongOperationStartedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ILongOperationStartedMessage> cmd,
                      Ref<IMessageOutput> sink);
};


} // namespace Vandrouka