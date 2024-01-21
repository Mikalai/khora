#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/ILanguageAddedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class LanguageAddedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<LanguageAddedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::ILanguageAddedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::ILanguageAddedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private