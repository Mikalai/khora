#pragma once

#include <string_view>

#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::Catalog::Messages {

class IEntryAddedMessage : public IMessage {
public:
  virtual Ref<IEntry> GetParent() const = 0;
  virtual Ref<IEntry> GetEntry() const = 0;
  virtual EntryPath GetPath() const = 0;
};

} // namespace Vandrouka::Catalog::Messages

DECLARE_IID(Vandrouka::Catalog::Messages::IEntryAddedMessage, 0xf9, 0x81, 0x34,
            0x88, 0x98, 0x6, 0x4b, 0x5f, 0xbf, 0xa1, 0x5, 0xb6, 0x81, 0x78,
            0xe4, 0xa1);
