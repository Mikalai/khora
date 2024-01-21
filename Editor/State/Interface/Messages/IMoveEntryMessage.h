#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IMoveEntryMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetSourcePath() const = 0;
  virtual Catalog::EntryPath GetTargetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IMoveEntryMessage, 0xe3, 0x50, 0x76,
            0xe8, 0x90, 0xeb, 0x43, 0x10, 0x9b, 0xc7, 0x3a, 0xc9, 0x83, 0xaf,
            0xc, 0x81);
