#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class ExportToFileMessageProcessor
    : public MessageProcessorBase<ExportToFileMessageProcessor, IDataModelState,
                                  IExportToFileMessage> {

public:
  void ProcessMessage(Ref<IDataModelState> s, Ref<IExportToFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka