#include "CopyEntryMessage.h"

namespace Vandrouka::State::Private::Messages {

Catalog::EntryPath CopyEntryMessage::GetSourcePath() const { return _src; }

Catalog::EntryPath CopyEntryMessage::GetTargetPath() const { return _dst; }

CopyEntryMessage::CopyEntryMessage(const Catalog::EntryPath &_src,
                                   const Catalog::EntryPath &_dst)
    : _src(_src), _dst(_dst) {}

} // namespace Vandrouka