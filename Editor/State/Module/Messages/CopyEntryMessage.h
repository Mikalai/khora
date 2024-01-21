#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ICopyEntryMessage.h>
#include <Catalog/Interface/EntryPath.h>

namespace Vandrouka::State::Private::Messages {

class CopyEntryMessage
    : public Fundamental::Private::MessageBase<CopyEntryMessage, State::Messages::ICopyEntryMessage> {
public:
  CopyEntryMessage(const Catalog::EntryPath &_src,
                   const Catalog::EntryPath &_dst);

  Catalog::EntryPath GetSourcePath() const override;
  Catalog::EntryPath GetTargetPath() const override;

private:
  Catalog::EntryPath _src;
  Catalog::EntryPath _dst;
};

} // namespace Vandrouka