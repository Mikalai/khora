#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../../ISystemFonts.h"
#include "../ViewerState.h"


namespace Vandrouka {

class FontsRefreshCompletedMessageProcessor
    : public MessageProcessorBase<FontsRefreshCompletedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IFontsRefreshCompletedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IFontsRefreshCompletedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka