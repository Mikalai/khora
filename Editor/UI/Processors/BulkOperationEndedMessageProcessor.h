#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IBulkOperationEndedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class BulkOperationEndedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<BulkOperationEndedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::IBulkOperationEndedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::IBulkOperationEndedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private