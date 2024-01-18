#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../../ISystemFonts.h"
#include "../ViewerState.h"


namespace Vandrouka {


class FontCompiledMessageProcessor
    : public MessageProcessorBase<FontCompiledMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  IFontCompiledMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<IFontCompiledMessage> &cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka