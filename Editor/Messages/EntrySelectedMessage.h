#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class EntrySelectedMessage
    : public MessageBase<EntrySelectedMessage, IEntrySelectedMessage> {
public:
  EntrySelectedMessage(EntryRef entry) : _entry{entry} {}

  EntryRef GetSelectedEntry() override { return _entry; }

private:
  EntryRef _entry;
};

} // namespace Vandrouka