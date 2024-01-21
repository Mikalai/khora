#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IResetModelMessage.h>

namespace Vandrouka::State::Private::Processors {

class ResetModelMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          ResetModelMessageProcessor, IDataModelState,
          State::Messages::IResetModelMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IResetModelMessage> cmd,
                      Ref<IMessageOutput> sink);
};
} // namespace Vandrouka::State::Private