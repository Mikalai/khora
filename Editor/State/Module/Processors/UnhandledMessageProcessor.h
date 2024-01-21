#pragma once

#include <State/Interface/IDataModelState.h>


#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private {

class UnhandledMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<UnhandledMessageProcessor, IDataModelState,
                                  IMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, const Ref<IMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private