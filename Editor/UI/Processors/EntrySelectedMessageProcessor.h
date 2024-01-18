#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"

namespace Vandrouka {

class EntrySelectedMessageProcessor
    : public MessageProcessorBase<EntrySelectedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IEntrySelectedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IEntrySelectedMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka