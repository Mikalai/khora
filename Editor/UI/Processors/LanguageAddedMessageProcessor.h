#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ViewerState.h"

namespace Vandrouka {


class LanguageAddedMessageProcessor
    : public MessageProcessorBase<LanguageAddedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  ILanguageAddedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<ILanguageAddedMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka