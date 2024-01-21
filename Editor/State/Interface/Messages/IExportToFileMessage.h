#pragma once

#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IExportToFileMessage : public IMessage {
public:
  virtual std::string GetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IExportToFileMessage, 0xb8, 0xe8, 0x64,
            0xbc, 0x4, 0xda, 0x45, 0xdb, 0xb5, 0x8c, 0x12, 0xd3, 0xe7, 0xc4,
            0x2a, 0x27);
