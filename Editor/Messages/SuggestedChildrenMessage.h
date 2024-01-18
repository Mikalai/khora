#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class SuggestedChildrenMessage
    : public MessageBase<SuggestedChildrenMessage, ISuggestedChildrenMessage> {
public:
  SuggestedChildrenMessage(std::string context, EntryPath path,
                           std::vector<Suggestion> suggestions)
      : _context{context}, _path{path}, _suggestions{suggestions} {}

  const std::string &GetContext() const override { return _context; }
  const EntryPath &GetPath() const override { return _path; }
  const std::vector<Suggestion> &GetSuggestions() const override {
    return _suggestions;
  }

private:
  std::string _context;
  EntryPath _path;
  std::vector<Suggestion> _suggestions;
};

} // namespace Vandrouka