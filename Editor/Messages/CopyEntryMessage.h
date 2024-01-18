#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class CopyEntryMessage
    : public MessageBase<CopyEntryMessage, ICopyEntryMessage> {
public:
  CopyEntryMessage(const EntryPath &_src, const EntryPath &_dst);

  EntryPath GetSourcePath() const override;
  EntryPath GetTargetPath() const override;

private:
  EntryPath _src;
  EntryPath _dst;
};

} // namespace Vandrouka