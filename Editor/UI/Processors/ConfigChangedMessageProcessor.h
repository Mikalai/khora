#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {

class ConfigChangedMessageProcessor
    : public MessageProcessorBase<ConfigChangedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IConfigChangedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IConfigChangedMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka