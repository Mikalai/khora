#include <string_view>
#include <unordered_set>

#include "../../DataModel/IDataModelState.h"
#include "../../IDataModel.h"
#include "../../Messages/CompileSceneMessage.h"
#include "../EditorMainWindow.h"
#include "EntryPropertyChangedMessageProcessor.h"

namespace Vandrouka {

static const std::unordered_set<std::string_view> PropertiesToRecompile{
    "Orientation",
    "Position",
    "Override",
    "Scale",
    "Font",
    "Value",
    "Color",
    "Color.R",
    "Color.G",
    "Color.B",
    "Color.A",
    "Offset",
    "Offset.X",
    "Offset.Y",
    "Offset.Z",
    "VerticalAxis",
    "VerticalAxis.X",
    "VerticalAxis.Y",
    "VerticalAxis.Z",
    "HorizontalAxis",
    "HorizontalAxis.X",
    "HorizontalAxis.Y",
    "HorizontalAxis.Z",
    "HorizontalAlignment",
    "VerticalAlignment",
    "LineSpacing",
    "ActiveLanguage"};

void EntryPropertyChangedMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<IEntryPropertyChangedMessage> cmd, Ref<IMessageOutput> sink) {
  if (!cmd->GetChangedEntry())
    return;

  if (PropertiesToRecompile.contains(cmd->GetProperty())) {
    state->GetState()->_dataModel->Execute(
        new CompileSceneMessage{{ROOT_SCENE}});
  }
}
} // namespace Vandrouka