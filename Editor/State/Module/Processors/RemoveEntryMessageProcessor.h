#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IRemoveEntryMessage.h>

namespace Vandrouka::State::Private::Processors {

class RemoveEntryMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          RemoveEntryMessageProcessor, IDataModelState,
          State::Messages::IRemoveEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IRemoveEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private::Processors