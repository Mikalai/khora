#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/ISelectEntryMessage.h>

namespace Vandrouka::State::Private::Processors {

class SelectEntryMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          SelectEntryMessageProcessor, IDataModelState,
          State::Messages::ISelectEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::ISelectEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};
} // namespace Vandrouka::State::Private