#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class LanguageRemovedMessage
    : public MessageBase<LanguageRemovedMessage, ILanguageRemovedMessage> {
public:
  LanguageRemovedMessage(std::string value) : _value{value} {}
  const std::string &GetValue() const override { return _value; }

private:
  std::string _value;
};

} // namespace Vandrouka