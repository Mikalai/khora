#pragma once

#include <Catalog/Interface/Messages/IPropertyChangedMessage.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::Catalog::Private::Messages {

class PropertyChangedMessage
    : public Fundamental::Private::MessageBase<
          PropertyChangedMessage, Catalog::Messages::IPropertyChangedMessage> {
public:
  PropertyChangedMessage(EntryRef owner, std::string_view property)
      : _owner{owner}, _property{property} {}

  EntryRef GetOwner() const override { return this->_owner; }

  const std::string_view GetProperty() const override {
    return this->_property;
  }

private:
  EntryRef _owner;
  std::string_view _property;
};

} // namespace Vandrouka::Catalog::Private::Messages