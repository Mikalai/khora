#pragma once

#include <Catalog/Interface/IConfigEntry.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {


class IConfigChangedMessage : public IMessage {
public:
  virtual Ref<Catalog::IConfigEntry> GetConfig() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IConfigChangedMessage, 0x1, 0xe7,
            0x7c, 0xf, 0xb5, 0x91, 0x4f, 0x5c, 0x9b, 0x78, 0x88, 0xb, 0x4d,
            0xa5, 0xde, 0x56);
