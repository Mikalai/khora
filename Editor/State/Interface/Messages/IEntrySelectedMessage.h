#pragma once

#include <string>
#include <Fundamental/Interface/IMessage.h>
#include <Catalog/Interface/IEntry.h>

namespace Vandrouka::State::Messages {

class IEntrySelectedMessage : public IMessage {
public:
  virtual Catalog::EntryRef GetSelectedEntry() = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IEntrySelectedMessage, 0x9a, 0xc9, 0xf8,
            0x28, 0x13, 0x67, 0x40, 0xa, 0xba, 0xc, 0x4f, 0x2d, 0xcb, 0xce,
            0xc4, 0x4f);
