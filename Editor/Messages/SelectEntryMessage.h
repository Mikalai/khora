#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class SelectEntryMessage
    : public MessageBase<SelectEntryMessage, ISelectEntryMessage> {
public:
  SelectEntryMessage(EntryPath path) : _path{path} {}

  EntryPath GetPath() const override { return _path; }

private:
  EntryPath _path;
};

} // namespace Vandrouka