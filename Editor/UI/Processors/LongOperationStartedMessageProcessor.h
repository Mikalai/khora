#pragma once

#include "../ViewerState.h"
#include <Fundamental/Interface/Messages/ILongOperationStartedMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::UI::Private::Processors {

class LongOperationStartedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          LongOperationStartedMessageProcessor, IEditorMainWindowStateWrapper,
          Fundamental::Messages::ILongOperationStartedMessage> {
public:
  void
  ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                 Ref<Fundamental::Messages::ILongOperationStartedMessage> cmd,
                 Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private