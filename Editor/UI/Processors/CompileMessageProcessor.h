#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {

class CompileMessageProcessor
    : public MessageProcessorBase<CompileMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ICompileMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ICompileMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka