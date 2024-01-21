#include "BulkOperationEndedMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {

void BulkOperationEndedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::IBulkOperationEndedMessage> cmd,
    Ref<IMessageOutput> sink) {

  auto ops = state->GetState()->_bulkOperation--;
  assert(ops >= 0);
  if (ops == 0) {
    if (!state->GetState()->_bulkErrors.empty()) {
      std::string bigMessage;
      for (auto &e : state->GetState()->_bulkErrors) {
        bigMessage.append(e);
        bigMessage.append("\n\r");
      }
      wxMessageBox(bigMessage, "Error", wxICON_ERROR);
    }
  }
}

} // namespace Vandrouka::UI::Private
