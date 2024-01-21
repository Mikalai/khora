#pragma once

#include <string_view>

#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::Catalog::Messages {

class IEntryRemovedMessage : public IMessage {
public:
  virtual Ref<IEntry> GetParent() const = 0;
  virtual Ref<IEntry> GetEntry() const = 0;
  virtual EntryPath GetPath() const = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::Messages::IEntryRemovedMessage, 0xe0, 0x97, 0x50, 0x9,
            0x42, 0xd7, 0x47, 0x45, 0xa2, 0xeb, 0xd8, 0x96, 0xa2, 0xf0, 0x8f,
            0x54);
