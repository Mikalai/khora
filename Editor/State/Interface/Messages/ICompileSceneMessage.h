#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ICompileSceneMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetRoot() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ICompileSceneMessage, 0x5d, 0xc8, 0x79,
            0x70, 0, 0xd0, 0x41, 0x8e, 0xba, 0x9b, 0x6f, 0xb8, 0x15, 0xa4, 0xe9,
            0x7e);
