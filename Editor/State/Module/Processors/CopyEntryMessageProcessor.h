#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/ICopyEntryMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private::Processors {

class CopyEntryMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<CopyEntryMessageProcessor, IDataModelState,
                                  State::Messages::ICopyEntryMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::ICopyEntryMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private