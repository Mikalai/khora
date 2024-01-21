#pragma once

#include <filesystem>
#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ISelectEntryMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ISelectEntryMessage, 0x64, 0x75, 0x91,
            0xe5, 0x9c, 0x70, 0x43, 0xb3, 0xbb, 0xa6, 0x1, 0x5c, 0x24, 0x6c,
            0xe0, 0x49);
