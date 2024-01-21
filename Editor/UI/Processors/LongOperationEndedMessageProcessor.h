#pragma once

#include "../ViewerState.h"
#include <Fundamental/Interface/Messages/ILongOperationEndedMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::UI::Private::Processors {

class LongOperationEndedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          LongOperationEndedMessageProcessor, IEditorMainWindowStateWrapper,
          Fundamental::Messages::ILongOperationEndedMessage> {
public:
  void
  ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                 Ref<Fundamental::Messages::ILongOperationEndedMessage> cmd,
                 Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private