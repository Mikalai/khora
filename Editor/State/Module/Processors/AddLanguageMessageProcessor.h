#pragma once

#include <State/Interface/IDataModelState.h>
#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IAddLanguageMessage.h>

namespace Vandrouka::State::Private::Processors {

class AddLanguageMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<AddLanguageMessageProcessor, IDataModelState,
                                  State::Messages::IAddLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IAddLanguageMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private