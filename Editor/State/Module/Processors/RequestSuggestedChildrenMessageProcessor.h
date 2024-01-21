#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IRequestSuggestedChildrenMessage.h>

namespace Vandrouka::State::Private::Processors {

class RequestSuggestedChildrenMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          RequestSuggestedChildrenMessageProcessor, IDataModelState,
          State::Messages::IRequestSuggestedChildrenMessage> {
public:
  void
  ProcessMessage(Ref<IDataModelState> state,
                 Ref<State::Messages::IRequestSuggestedChildrenMessage> cmd,
                 Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private::Processors