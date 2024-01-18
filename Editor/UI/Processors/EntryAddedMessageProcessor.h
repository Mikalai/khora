#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"

namespace Vandrouka {

class EntryAddedMessageProcessor
    : public MessageProcessorBase<EntryAddedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IEntryAddedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IEntryAddedMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka