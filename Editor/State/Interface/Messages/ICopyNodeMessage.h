#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ICopyNodeMessage : public IMessage {
public:
  virtual Catalog::EntryPath GetSourcePath() const = 0;
  virtual Catalog::EntryPath GetTargetPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ICopyNodeMessage, 0xae, 0x43, 0x7f,
            0xb1, 0xad, 0x35, 0x4f, 0x27, 0xbd, 0x6f, 0x8b, 0xe0, 0xf2, 0xac,
            0x1d, 0x24);
