#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class RenameEntryMessage
    : public MessageBase<RenameEntryMessage, IRenameEntryMessage> {
public:
  RenameEntryMessage(EntryPath _oldPath, EntryPath _newPath)
      : _oldPath(_oldPath), _newPath(_newPath) {}

  EntryPath GetOldPath() const override { return _oldPath; }
  EntryPath GetNewPath() const override { return _newPath; }

private:
  EntryPath _oldPath;
  EntryPath _newPath;
};

} // namespace Vandrouka