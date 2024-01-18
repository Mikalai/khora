#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"

namespace Vandrouka {


class SuggestedChildrenMessageProcessor
    : public MessageProcessorBase<SuggestedChildrenMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ISuggestedChildrenMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ISuggestedChildrenMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka