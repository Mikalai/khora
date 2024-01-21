#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/ISaveToFileMessage.h>

namespace Vandrouka::State::Private::Processors {

class SaveToFileMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          SaveToFileMessageProcessor, IDataModelState,
          State::Messages::ISaveToFileMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::ISaveToFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private::Processors