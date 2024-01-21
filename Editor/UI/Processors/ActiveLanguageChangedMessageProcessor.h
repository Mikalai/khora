#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IActiveLanguageChangedMessage.h>

#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class ActiveLanguageChangedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<ActiveLanguageChangedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::IActiveLanguageChangedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::IActiveLanguageChangedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private