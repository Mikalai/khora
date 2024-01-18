#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class RemoveEntryMessage
    : public MessageBase<RemoveEntryMessage, IRemoveEntryMessage> {
public:
  RemoveEntryMessage(EntryPath path) : _path{path} {}

  EntryPath GetPath() const override { return _path; }

private:
  EntryPath _path;
};

} // namespace Vandrouka