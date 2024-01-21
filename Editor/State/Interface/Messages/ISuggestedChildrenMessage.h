#pragma once

#include <string>
#include <vector>
#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ISuggestedChildrenMessage : public IMessage {
public:
  struct Suggestion {
    std::string Type;
    std::string Name;
  };

  virtual const std::string &GetContext() const = 0;
  ;
  virtual const Catalog::EntryPath &GetPath() const = 0;
  virtual const std::vector<Suggestion> &GetSuggestions() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ISuggestedChildrenMessage, 0x2f, 0x1e,
            0x9e, 0xec, 0x7a, 0x18, 0x40, 0x10, 0x8a, 0x45, 0x49, 0xd8, 0x9f,
            0x8d, 0xf2, 0xe4);
