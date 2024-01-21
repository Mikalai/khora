#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IRenameEntryMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private {

class RenameEntryMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<RenameEntryMessageProcessor, IDataModelState,
                                  State::Messages::IRenameEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IRenameEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private