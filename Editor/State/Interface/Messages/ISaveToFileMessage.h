#pragma once

#include <filesystem>
#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ISaveToFileMessage : public IMessage {
public:
  virtual std::filesystem::path GetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ISaveToFileMessage, 0xc1, 0x40, 0x53,
            0xec, 0xf8, 0x61, 0x47, 0x31, 0xae, 0x3e, 0xa4, 0x1, 0xee, 0xc6,
            0x26, 0x85);
