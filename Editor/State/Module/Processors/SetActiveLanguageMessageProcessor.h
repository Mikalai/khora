#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/ISetActiveLanguageMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private::Processors {

class SetActiveLanguageMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<SetActiveLanguageMessageProcessor,
                                  IDataModelState, State::Messages::ISetActiveLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      const Ref<State::Messages::ISetActiveLanguageMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private