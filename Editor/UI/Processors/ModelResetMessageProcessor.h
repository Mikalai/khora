#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {

class ModelResetMessageProcessor
    : public MessageProcessorBase<ModelResetMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IModelResetMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IModelResetMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka