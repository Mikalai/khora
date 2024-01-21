#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class UnhandledMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<UnhandledMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      const Ref<IMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private