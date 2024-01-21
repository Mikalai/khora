#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IRenameEntryMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetOldPath() const = 0;
  virtual Catalog::EntryPath GetNewPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IRenameEntryMessage, 0x3e, 0x6c, 0x9,
            0x9d, 0x77, 0xe, 0x4a, 0x9f, 0xba, 0xd8, 0x9a, 0xde, 0xd1, 0x79,
            0xf4, 0x1f);
