#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {

class LanguageRemovedMessageProcessor
    : public MessageProcessorBase<LanguageRemovedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ILanguageRemovedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ILanguageRemovedMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka