#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IMoveEntryMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private::Processors {

class MoveEntryMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<MoveEntryMessageProcessor, IDataModelState,
                                  State::Messages::IMoveEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IMoveEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private