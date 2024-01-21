#pragma once

#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::Fonts::Messages {

class ICompileFontMessage : public Fundamental::IMessage {
public:
  virtual const std::string &GetDisplayName() const = 0;
  virtual Ref<IReferenced> GetState() const = 0;
};

} // namespace Vandrouka::Fonts::Messages

DECLARE_IID(Vandrouka::Fonts::Messages::ICompileFontMessage, 0x26, 0x4c, 0x4b,
            0xb7, 0x6c, 0x29, 0x49, 0x4b, 0xa5, 0x9f, 0xd9, 0x30, 0x8e, 0x8f,
            0x1a, 0x1f);
