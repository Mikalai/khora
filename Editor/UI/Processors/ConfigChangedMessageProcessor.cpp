#include "ConfigChangedMessageProcessor.h"
#include <Catalog/Interface/IConfigEntry.h>
#include "../EditorMainWindow.h"

namespace Vandrouka::UI::Private::Processors {
void ConfigChangedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::IConfigChangedMessage> cmd,
    Ref<IMessageOutput> sink) {
  state->GetState()->_config = cmd->GetConfig();
  state->GetState()->UpdateConfig();
}
} // namespace Vandrouka::UI::Private