#pragma once

#include <State/Interface/IDataModelState.h>
#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/Messages/IExportToFileMessage.h>

namespace Vandrouka::State::Private::Processors {

class ExportToFileMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<ExportToFileMessageProcessor, IDataModelState,
                                  State::Messages::IExportToFileMessage> {

public:
  void ProcessMessage(Ref<IDataModelState> s,
                      Ref<State::Messages::IExportToFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private