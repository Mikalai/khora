#include "SceneCompeledMessageProcessor.h"
#include "../EditorMainWindow.h"

namespace Vandrouka {
void SceneCompeledMessageProcessor::ProcessMessage(
    Ref<IEditorMainWindowStateWrapper> state, Ref<ISceneCompeledMessage> cmd,
    Ref<IMessageOutput> sink) {
  auto s = state->GetState();
  auto _root = s->_root;
  auto viewerWindow = s->viewerWindow;

  for (auto child : _root->children) {
    s->_cleanup.emplace_back(60, child);
  }

  _root->children.clear();

  if (cmd->GetRoot()) {
    _root->addChild(cmd->GetRoot());
  }

  viewerWindow->viewer->compileManager->compile(_root);
}
} // namespace Vandrouka