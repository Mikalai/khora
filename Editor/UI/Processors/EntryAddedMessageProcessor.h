#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <Catalog/Interface/Messages/IEntryAddedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class EntryAddedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<EntryAddedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  Catalog::Messages::IEntryAddedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<Catalog::Messages::IEntryAddedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private