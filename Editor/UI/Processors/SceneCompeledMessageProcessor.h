#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/ISceneCompeledMessage.h>
#include "../ViewerState.h"

namespace Vandrouka::UI::Private::Processors {

class SceneCompeledMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<SceneCompeledMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  State::Messages::ISceneCompeledMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<State::Messages::ISceneCompeledMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private