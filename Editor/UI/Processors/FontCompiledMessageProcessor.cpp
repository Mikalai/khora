#include "FontCompiledMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {

void FontCompiledMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<IFontCompiledMessage> &cmd,
    Ref<IMessageOutput> sink) {

  if (cmd->GetState())
    return;

  auto _root = state->GetState()->_root;
  auto viewerWindow = state->GetState()->viewerWindow;

  for (auto child : _root->children) {
    state->GetState()->_cleanup.emplace_back(60, child);
  }

  _root->children.clear();

  if (cmd->GetRoot()) {
    _root->addChild(cmd->GetRoot());
  }

  viewerWindow->viewer->compileManager->compile(_root);
}

} // namespace Vandrouka
