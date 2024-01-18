#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"


namespace Vandrouka {

class SceneCompeledMessageProcessor
    : public MessageProcessorBase<SceneCompeledMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ISceneCompeledMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ISceneCompeledMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka