#include "UnhandledMessageProcessor.h"

namespace Vandrouka::UI::Private::Processors {

void UnhandledMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, const Ref<IMessage> cmd,
    Ref<IMessageOutput> sink) {
  sink->SubmitError(CreateError(LOG_NOT_IMPLEMENTED,
                                std::string{"Message handler is not found. "} +
                                    ToString(cmd)));
}

} // namespace Vandrouka::UI::Private::Processors