#include "CopyEntryMessage.h"

namespace Vandrouka {

EntryPath CopyEntryMessage::GetSourcePath() const { return _src; }

EntryPath CopyEntryMessage::GetTargetPath() const { return _dst; }

CopyEntryMessage::CopyEntryMessage(const EntryPath &_src, const EntryPath &_dst)
    : _src(_src), _dst(_dst) {}

} // namespace Vandrouka