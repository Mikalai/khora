#pragma once

#include <Fonts/Interface/Messages/IFontCompiledMessage.h>
#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>

namespace Vandrouka::State::Private::Processors {

class FontCompiledMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          FontCompiledMessageProcessor, IDataModelState,
          Fonts::Messages::IFontCompiledMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<Fonts::Messages::IFontCompiledMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private::Data::Processors
