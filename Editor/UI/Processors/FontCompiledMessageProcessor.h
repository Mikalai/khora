#pragma once



#include <Fundamental/Module/MessageProcessor.h>
#include <Fonts/Interface.h>
#include "../ViewerState.h"


namespace Vandrouka::UI::Private::Processors {


class FontCompiledMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<FontCompiledMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  Fonts::Messages::IFontCompiledMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<Fonts::Messages::IFontCompiledMessage> &cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private