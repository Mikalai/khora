#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka {

class AddLanguageMessageProcessor
    : public MessageProcessorBase<AddLanguageMessageProcessor, IDataModelState,
                                  IAddLanguageMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<IAddLanguageMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka