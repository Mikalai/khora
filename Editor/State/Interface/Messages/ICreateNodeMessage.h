#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ICreateNodeMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetPath() const = 0;
  virtual std::string GetType() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ICreateNodeMessage, 0xc9, 0x40, 0x9d,
            0xba, 0x9c, 0x9c, 0x41, 0x8c, 0x8e, 0xe4, 0x9b, 0xa5, 0x56, 0x8d,
            0xa1, 0xd3);
