#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/ICopyNodeMessage.h>

namespace Vandrouka::State::Private::Processors {

class CopyNodeMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          CopyNodeMessageProcessor, IDataModelState,
          State::Messages::ICopyNodeMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::ICopyNodeMessage> cmd,
                      Ref<IMessageOutput> sink);
};
} // namespace Vandrouka::State::Private::Processors