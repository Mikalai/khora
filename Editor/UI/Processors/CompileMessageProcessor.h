#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/ICompileMessage.h>
#include "../ViewerState.h"


namespace Vandrouka::UI::Private::Processors {

class CompileMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<CompileMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::ICompileMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::ICompileMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private