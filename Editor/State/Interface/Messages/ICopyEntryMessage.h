#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ICopyEntryMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetSourcePath() const = 0;
  virtual Catalog::EntryPath GetTargetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ICopyEntryMessage, 0x2b, 0xc, 0x71, 0xc,
            0xb3, 0x98, 0x4b, 0x56, 0xab, 0x4a, 0xa0, 0x29, 0x4b, 0x9f, 0xde,
            0x1a);
