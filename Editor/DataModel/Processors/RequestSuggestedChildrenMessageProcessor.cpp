#include "RequestSuggestedChildrenMessageProcessor.h"
#include "../../Messages/SuggestedChildrenMessage.h"

namespace Vandrouka {

void RequestSuggestedChildrenMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<IRequestSuggestedChildrenMessage> cmd,
    Ref<IMessageOutput> sink) {

  auto entry = state->GetDir()->FindEntry(cmd->GetPath());
  if (!entry) {
    sink->SubmitError(new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                                       cmd->GetPath().Path));
    return;
  }

  std::vector<ISuggestedChildrenMessage::Suggestion> suggestions;
  switch (entry->GetType()) {
  case EntryType::Transform:
  case EntryType::Material:
  case EntryType::Group:
  case EntryType::Directory:
    suggestions.emplace_back("Group", "Group");
    // r.Suggestions.emplace_back(magic_enum::enum_name(EntryType::Material),
    // magic_enum::enum_name(EntryType::Material));
    suggestions.emplace_back("Transform", "Transform");
    suggestions.emplace_back("Localized", "Localized");
    suggestions.emplace_back("Text", "Text");
    break;

  case EntryType::Geometry:
  case EntryType::Config:
  case EntryType::Text:
    break;

  case EntryType::Localized: {
    auto config = state->GetConfig();
    for (auto l : config->GetLanguages()) {
      if (!state->GetDir()->FindEntry(cmd->GetPath().Append(l))) {
        suggestions.emplace_back("Group", l);
      }
    }
  } break;
  }

  sink->SubmitMessage(new SuggestedChildrenMessage{
      cmd->GetContext(), cmd->GetPath(), std::move(suggestions)});
}

} // namespace Vandrouka