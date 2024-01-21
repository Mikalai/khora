#pragma once

#include "../ViewerState.h"
#include <Catalog/Interface/Messages/IEntryRemovedMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::UI::Private::Processors {

class EntryRemovedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          EntryRemovedMessageProcessor, IEditorMainWindowStateWrapper,
          Catalog::Messages::IEntryRemovedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<Catalog::Messages::IEntryRemovedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private