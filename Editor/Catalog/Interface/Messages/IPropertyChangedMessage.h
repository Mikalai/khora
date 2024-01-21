#pragma once

#include <string_view>

#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::Catalog::Messages {

class IPropertyChangedMessage : public IMessage {
public:
  virtual Ref<IEntry> GetOwner() const = 0;
  virtual const std::string_view GetProperty() const = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::Messages::IPropertyChangedMessage, 0x34, 0x3, 0x9c, 0xf,
            0x70, 0xd9, 0x47, 0x30, 0xb6, 0x30, 0xd5, 0xce, 0xca, 0x43, 0xbe,
            0x57);
