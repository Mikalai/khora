#pragma once

#include <string>
#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IModelResetMessage : public IMessage {
public:
  virtual Ref<Catalog::IEntry> GetRoot() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IModelResetMessage, 0x93, 0xaf, 0x47,
            0xb9, 0xf2, 0x54, 0x44, 0xcc, 0x85, 0x3b, 0xd1, 0x2f, 0x25, 0x3d,
            0xf7, 0x4b);
