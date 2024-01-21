#include "RequestSuggestedChildrenMessageProcessor.h"
#include <State/Interface/Messages/ISuggestedChildrenMessage.h>
#include <State/Module/Messages/SuggestedChildrenMessage.h>

namespace Vandrouka::State::Private::Processors {

void RequestSuggestedChildrenMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state,
    Ref<State::Messages::IRequestSuggestedChildrenMessage> cmd,
    Ref<IMessageOutput> sink) {

  auto entry = state->GetDir()->FindEntry(cmd->GetPath());
  if (!entry) {
    sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetPath().Path));
    return;
  }

  std::vector<State::Messages::ISuggestedChildrenMessage::Suggestion>
      suggestions;
  switch (entry->GetType()) {
  case Catalog::EntryType::Transform:
  case Catalog::EntryType::Material:
  case Catalog::EntryType::Group:
  case Catalog::EntryType::Directory:
    suggestions.emplace_back("Group", "Group");
    // r.Suggestions.emplace_back(magic_enum::enum_name(EntryType::Material),
    // magic_enum::enum_name(EntryType::Material));
    suggestions.emplace_back("Transform", "Transform");
    suggestions.emplace_back("Localized", "Localized");
    suggestions.emplace_back("Text", "Text");
    break;

  case Catalog::EntryType::Geometry:
  case Catalog::EntryType::Config:
  case Catalog::EntryType::Text:
    break;

  case Catalog::EntryType::Localized: {
    auto config = state->GetConfig();
    for (auto l : config->GetLanguages()) {
      if (!state->GetDir()->FindEntry(cmd->GetPath().Append(l))) {
        suggestions.emplace_back("Group", l);
      }
    }
  } break;
  }

  sink->SubmitMessage(new Messages::SuggestedChildrenMessage{
      cmd->GetContext(), cmd->GetPath(), std::move(suggestions)});
}

} // namespace Vandrouka::State::Private::Processors
