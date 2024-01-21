#pragma once

#include <Fundamental/Module/MessageProcessor.h>
#include <State/Interface/IDataModelState.h>
#include <State/Interface/Messages/IFontsCompilationJobsCompleteMessage.h>

namespace Vandrouka::State::Private::Processors {

class FontsCompilationJobsCompleteMessageProcessor
    : public Fundamental::Private::MessageProcessorBase<
          FontsCompilationJobsCompleteMessageProcessor, IDataModelState,
          State::Messages::IFontsCompilationJobsCompleteMessage> {
public:
  void
  ProcessMessage(Ref<IDataModelState> state,
                 Ref<State::Messages::IFontsCompilationJobsCompleteMessage> cmd,
                 Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::State::Private