#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class FontsCompilationJobsCompleteMessageProcessor
    : public MessageProcessorBase<FontsCompilationJobsCompleteMessageProcessor,
                                  IDataModelState,
                                  IFontsCompilationJobsCompleteMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<IFontsCompilationJobsCompleteMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka