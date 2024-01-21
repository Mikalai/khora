#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IImportFromFileMessage.h>

#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private::Processors {

class ImportFromFileMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          ImportFromFileMessageProcessor, IDataModelState,
          State::Messages::IImportFromFileMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<State::Messages::IImportFromFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private