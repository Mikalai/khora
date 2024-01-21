#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IRemoveEntryMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IRemoveEntryMessage, 0xa5, 0x19, 0x2d,
            0x88, 0x79, 0x5c, 0x49, 0x3, 0xb8, 0xaf, 0x1e, 0x88, 0x6a, 0xd6,
            0x5a, 0xe8);
