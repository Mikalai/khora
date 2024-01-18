#include "ConfigChangedMessageProcessor.h"
#include "../../IConfigEntry.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {
void ConfigChangedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<IConfigChangedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->_config = cmd->GetConfig();
  state->GetState()->UpdateConfig();
}
} // namespace Vandrouka