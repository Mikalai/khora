#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {

class EntryPropertyChangedMessageProcessor
    : public MessageProcessorBase<EntryPropertyChangedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IEntryPropertyChangedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IEntryPropertyChangedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka