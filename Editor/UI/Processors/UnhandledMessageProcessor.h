#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"

namespace Vandrouka {

class UnhandledMessageProcessor
    : public MessageProcessorBase<UnhandledMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      const Ref<IMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka