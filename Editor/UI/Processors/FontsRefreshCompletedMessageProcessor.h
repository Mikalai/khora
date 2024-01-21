#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <Fonts/Interface.h>
#include <UI/ViewerState.h>


namespace Vandrouka::UI::Private::Processors {

class FontsRefreshCompletedMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<FontsRefreshCompletedMessageProcessor,
                                  IEditorMainWindowStateWrapper,
                                  Fonts::Messages::IFontsRefreshCompletedMessage> {
public:
  void ProcessMessage(Ref<IEditorMainWindowStateWrapper> state,
                      Ref<Fonts::Messages::IFontsRefreshCompletedMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::UI::Private