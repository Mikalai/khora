#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {


class EntryRemovedMessageProcessor
    : public MessageProcessorBase<EntryRemovedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IEntryRemovedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IEntryRemovedMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka