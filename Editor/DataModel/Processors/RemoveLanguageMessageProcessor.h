#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class RemoveLanguageMessageProcessor
    : public MessageProcessorBase<RemoveLanguageMessageProcessor,
                                  IDataModelState, IRemoveLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      Ref<IRemoveLanguageMessage> cmd, Ref<IMessageOutput> sink);
};

} // namespace Vandrouka