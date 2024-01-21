#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IImportFileMessage.h>
#include <State/Interface/IDataModelState.h>

namespace Vandrouka::State::Private::Processors {

class ImportFileMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<ImportFileMessageProcessor, IDataModelState,
                                  State::Messages::IImportFileMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> model,
                      Ref<State::Messages::IImportFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private