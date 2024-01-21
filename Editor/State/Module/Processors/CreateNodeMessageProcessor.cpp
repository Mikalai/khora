#include "CreateNodeMessageProcessor.h"
#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Interface/ITransformEntry.h>
#include <Catalog/Interface/ILocalizedEntry.h>

namespace Vandrouka::State::Private::Processors {

void CreateNodeMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::ICreateNodeMessage> cmd,
    Ref<IMessageOutput> sink) {
  int suffix = 0;
  auto path = cmd->GetPath();

  while (auto node = state->GetDir()->FindEntry(path)) {
    path = {cmd->GetPath().Path + "." + std::to_string(suffix++)};
  }

  Catalog::EntryRef entry;

  if (cmd->GetType() == "Group") {
    entry = Create<Instances::Catalog::GroupEntry, Catalog::IEntry>();
  } else if (cmd->GetType() == "Transform") {
    entry = Create<Instances::Catalog::TransformProxyEntry, Catalog::IEntry>();
  } else if (cmd->GetType() == "Localized") {
    entry = Create<Instances::Catalog::LocalizedEntry, Catalog::IEntry>();
  } else if (cmd->GetType() == "Text") {
    entry = Create<Instances::Catalog::TextEntry, Catalog::IEntry>();
  }

  if (entry) {
    state->GetDir()->Add(path, entry);
  }
}

} // namespace Vandrouka::State::Private