#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/ILanguageRemovedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class LanguageRemovedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<LanguageRemovedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::ILanguageRemovedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::ILanguageRemovedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private