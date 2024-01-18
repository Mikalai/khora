#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class SetActiveLanguageMessageProcessor
    : public MessageProcessorBase<SetActiveLanguageMessageProcessor,
                                  IDataModelState, ISetActiveLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state,
                      const Ref<ISetActiveLanguageMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka