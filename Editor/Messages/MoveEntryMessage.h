#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class MoveEntryMessage
    : public MessageBase<MoveEntryMessage, IMoveEntryMessage> {
public:
  MoveEntryMessage(EntryPath src, EntryPath dst) : _src{src}, _dst{dst} {}
  EntryPath GetSourcePath() const override { return _src; }
  EntryPath GetTargetPath() const override { return _dst; }

private:
  EntryPath _src;
  EntryPath _dst;
};

} // namespace Vandrouka