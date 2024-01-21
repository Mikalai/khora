#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/ICreateNodeMessage.h>

namespace Vandrouka::State::Private::Processors {

class CreateNodeMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          CreateNodeMessageProcessor, IDataModelState,
          State::Messages::ICreateNodeMessage> {

public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::ICreateNodeMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private::Processors