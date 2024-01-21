#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IModelResetMessage.h>
#include "../ViewerState.h"


namespace Vandrouka::UI::Private::Processors {

class ModelResetMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<ModelResetMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::IModelResetMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::IModelResetMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private