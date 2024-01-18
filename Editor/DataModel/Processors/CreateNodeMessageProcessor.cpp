#include "CreateNodeMessageProcessor.h"
#include "../../IGroupEntry.h"
#include "../../ITransformEntry.h"
#include "../../ILocalizedEntry.h"

namespace Vandrouka {

void CreateNodeMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<ICreateNodeMessage> cmd,
    Ref<IMessageOutput> sink) {
  int suffix = 0;
  auto path = cmd->GetPath();

  while (auto node = state->GetDir()->FindEntry(path)) {
    path = {cmd->GetPath().Path + "." + std::to_string(suffix++)};
  }

  EntryRef entry;

  if (cmd->GetType() == "Group") {
    entry = Create<GroupEntry, IEntry>();
  } else if (cmd->GetType() == "Transform") {
    entry = Create<TransformProxyEntry, IEntry>();
  } else if (cmd->GetType() == "Localized") {
    entry = Create<LocalizedEntry, IEntry>();
  } else if (cmd->GetType() == "Text") {
    entry = Create<TextEntry, IEntry>();
  }

  if (entry) {
    state->GetDir()->Add(path, entry);
  }
}

} // namespace Vandrouka