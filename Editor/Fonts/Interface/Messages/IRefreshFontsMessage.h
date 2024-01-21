#pragma once

#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::Fonts::Messages {

class IRefreshFontsMessage : public IMessage {
public:
  virtual bool GetForce() const = 0;
};
} // namespace Vandrouka::Fonts::Messages

DECLARE_IID(Vandrouka::Fonts::Messages::IRefreshFontsMessage, 0xb1, 0x9b, 0x2a,
            0xb3, 0x65, 0xff, 0x4a, 0x6a, 0x8d, 0x3, 0xf0, 0x9a, 0xa5, 0x94,
            0x79, 0x4a);
