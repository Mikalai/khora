#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class ImportFromFileMessageProcessor
    : public MessageProcessorBase<ImportFromFileMessageProcessor,
                                  IDataModelState, IImportFromFileMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<IImportFromFileMessage> cmd, Ref<IMessageOutput> sink);
};


} // namespace Vandrouka