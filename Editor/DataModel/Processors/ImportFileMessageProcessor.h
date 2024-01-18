#pragma once

#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../IDataModelState.h"

namespace Vandrouka {

class ImportFileMessageProcessor
    : public MessageProcessorBase<ImportFileMessageProcessor, IDataModelState,
                                  IImportFileMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> model, Ref<IImportFileMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka