#include "SuggestedChildrenMessageProcessor.h"
#include "../EditorMainWindow.h"
#include <State/Module/Messages/CreateNodeMessage.h>

namespace Vandrouka::UI::Private::Processors {

void SuggestedChildrenMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state,
    Ref<State::Messages::ISuggestedChildrenMessage> cmd,
    Ref<IMessageOutput> sink) {
  if (cmd->GetContext() == "popup") {
    wxMenu menu;
    for (auto e : cmd->GetSuggestions()) {
      auto item = menu.Append(wxID_ANY, e.Name);

      menu.Bind(
          wxEVT_COMMAND_MENU_SELECTED,
          [state, cmd, e, this](wxCommandEvent &) mutable {
            state->GetState()->_dataModel->Execute(
                new State::Private::Messages::CreateNodeMessage{cmd->GetPath().Append(e.Name), e.Type});
          },
          item->GetId());
    }

    {
      menu.AppendSeparator();

      auto item = menu.Append(wxID_ANY, "Copy");

      menu.Bind(
          wxEVT_COMMAND_MENU_SELECTED,
          [state, cmd, this](wxCommandEvent &) mutable {
            state->GetState()->SaveCurrentSelectionPath();
          },
          item->GetId());
    }

    if (state->GetState()->_copyNode.IsValid()) {
      auto item = menu.Append(wxID_ANY, "Paste");

      menu.Bind(
          wxEVT_COMMAND_MENU_SELECTED,
          [state, cmd, this](wxCommandEvent &) mutable {
            state->GetState()->PasteEntryCopy();
          },
          item->GetId());
    }

    state->GetState()->PopupMenu(&menu);
  }
}

} // namespace Vandrouka::UI::Private