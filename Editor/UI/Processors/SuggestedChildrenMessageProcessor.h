#pragma once

#include "../ViewerState.h"
#include <State/Interface/Messages/ISuggestedChildrenMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::UI::Private::Processors {

class SuggestedChildrenMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          SuggestedChildrenMessageProcessor, IEditorMainWindowStateWrapper,
          State::Messages::ISuggestedChildrenMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::ISuggestedChildrenMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private