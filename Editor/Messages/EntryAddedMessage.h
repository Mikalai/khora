#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class EntryAddedMessage
    : public MessageBase<EntryAddedMessage, IEntryAddedMessage> {
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

} // namespace Vandrouka