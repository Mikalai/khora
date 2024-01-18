#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class RenameLanguageMessageProcessor
    : public MessageProcessorBase<RenameLanguageMessageProcessor,
                                  IDataModelState, IRenameLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<IRenameLanguageMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka