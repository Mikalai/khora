#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"
#include "../../LongOperationNotification.h"

namespace Vandrouka {

class LongOperationEndedMessageProcessor
    : public MessageProcessorBase<LongOperationEndedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ILongOperationEndedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ILongOperationEndedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka