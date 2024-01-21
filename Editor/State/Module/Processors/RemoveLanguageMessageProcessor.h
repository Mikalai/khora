#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IRemoveLanguageMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private::Processors {

class RemoveLanguageMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<RemoveLanguageMessageProcessor,
                                  IDataModelState, State::Messages::IRemoveLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IRemoveLanguageMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private
