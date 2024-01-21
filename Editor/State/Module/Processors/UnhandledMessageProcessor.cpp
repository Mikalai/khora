#include "UnhandledMessageProcessor.h"

namespace Vandrouka::State::Private {

void UnhandledMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                               const Ref<IMessage> cmd,
                                               Ref<IMessageOutput> sink) {
  if (auto s = cmd.Cast<IToString>(); s) {
    sink->SubmitError(CreateError(LOG_NOT_IMPLEMENTED,
                                  std::string{"Message handler is not found."} + s->ToString()));
  } else {
    sink->SubmitError(CreateError(LOG_NOT_IMPLEMENTED,
                                  std::string{"Message handler is not found"}));
  }
}

} // namespace Vandrouka::State::Private