#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <Catalog/Interface/Messages/IPropertyChangedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class EntryPropertyChangedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<EntryPropertyChangedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  Catalog::Messages::IPropertyChangedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<Catalog::Messages::IPropertyChangedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private