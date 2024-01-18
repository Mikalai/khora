#pragma once

#include "../../MessageProcessor.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../ViewerState.h"

namespace Vandrouka {

class ActiveLanguageChangedMessageProcessor
    : public MessageProcessorBase<ActiveLanguageChangedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IActiveLanguageChangedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IActiveLanguageChangedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka