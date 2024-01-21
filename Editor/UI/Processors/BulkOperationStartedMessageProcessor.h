#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IBulkOperationStartedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class BulkOperationStartedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<BulkOperationStartedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::IBulkOperationStartedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::IBulkOperationStartedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private