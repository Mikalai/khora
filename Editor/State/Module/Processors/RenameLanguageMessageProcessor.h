#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IRenameLanguageMessage.h>

namespace Vandrouka::State::Private::Processors {

class RenameLanguageMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          RenameLanguageMessageProcessor, IDataModelState,
          State::Messages::IRenameLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IRenameLanguageMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private::Processors