#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ISuggestedChildrenMessage.h>

namespace Vandrouka::State::Private::Messages {

class SuggestedChildrenMessage
    : public Fundamental::Private::MessageBase<
          SuggestedChildrenMessage,
          State::Messages::ISuggestedChildrenMessage> {
public:
  SuggestedChildrenMessage(std::string context, Catalog::EntryPath path,
                           std::vector<Suggestion> suggestions)
      : _context{context}, _path{path}, _suggestions{suggestions} {}

  const std::string &GetContext() const override { return _context; }
  const Catalog::EntryPath &GetPath() const override { return _path; }
  const std::vector<Suggestion> &GetSuggestions() const override {
    return _suggestions;
  }

private:
  std::string _context;
  Catalog::EntryPath _path;
  std::vector<Suggestion> _suggestions;
};

} // namespace Vandrouka::State::Private::Messages