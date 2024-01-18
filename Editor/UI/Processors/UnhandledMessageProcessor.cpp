#include "UnhandledMessageProcessor.h"

namespace Vandrouka {

void UnhandledMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, const Ref<IMessage> cmd,
    Ref<IMessageOutput> sink) {
  sink->SubmitError(
      new GenericError(LOG_LEVEL_ERROR, LOG_NOT_IMPLEMENTED,
                       std::string{"Message handler is not found. "} + ToString(cmd)));
}

} // namespace Vandrouka