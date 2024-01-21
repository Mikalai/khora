#pragma once

#include "../ViewerState.h"
#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IEntrySelectedMessage.h>

namespace Vandrouka::UI::Private::Processors {

class EntrySelectedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          EntrySelectedMessageProcessor, IEditorMainWindowStateWrapper,
          State::Messages::IEntrySelectedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::IEntrySelectedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private