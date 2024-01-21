#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IConfigChangedMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class ConfigChangedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<ConfigChangedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::IConfigChangedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::IConfigChangedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private