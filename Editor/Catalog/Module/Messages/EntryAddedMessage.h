#pragma once

#include <Catalog/Interface/Messages/IEntryAddedMessage.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::Catalog::Private::Messages {

class EntryAddedMessage
    : public Fundamental::Private::MessageBase<EntryAddedMessage,
                                               Catalog::Messages::IEntryAddedMessage> {
public:
  EntryAddedMessage(EntryPath path, EntryRef entry, EntryRef parent)
      : _path{path}, _entry{entry}, _parent{parent} {}

  EntryPath GetPath() const override { return this->_path; }

  EntryRef GetEntry() const override { return this->_entry; }
  EntryRef GetParent() const override { return this->_parent; }

private:
  EntryPath _path;
  EntryRef _entry;
  EntryRef _parent;
};

} // namespace Vandrouka::Catalog::Private::Messages