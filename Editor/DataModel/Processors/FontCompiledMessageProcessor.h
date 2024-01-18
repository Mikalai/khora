#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"

namespace Vandrouka::Data::Processors {

class FontCompiledMessageProcessor
    : public MessageProcessorBase<FontCompiledMessageProcessor, IDataModelState,
                                  IFontCompiledMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> state, Ref<IFontCompiledMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka