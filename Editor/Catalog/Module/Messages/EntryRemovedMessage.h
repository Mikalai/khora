#pragma once

#include <Catalog/Interface/Messages/IEntryRemovedMessage.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::Catalog::Private::Messages {

class EntryRemovedMessage
    : public Fundamental::Private::MessageBase<
          EntryRemovedMessage, Catalog::Messages::IEntryRemovedMessage> {
public:
  EntryRemovedMessage(EntryPath path, EntryRef entry, EntryRef parent)
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