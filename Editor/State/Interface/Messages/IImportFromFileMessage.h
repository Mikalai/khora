#pragma once

#include <filesystem>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IImportFromFileMessage : public IMessage {
public:
  virtual std::filesystem::path GetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IImportFromFileMessage, 0x70, 0xb0,
            0x39, 0xc5, 0xd9, 0xe4, 0x46, 0x4c, 0x91, 0x52, 0x17, 0x6, 0x3d,
            0x25, 0x42, 0xc8);
