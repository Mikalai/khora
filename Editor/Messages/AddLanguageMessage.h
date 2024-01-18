#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class AddLanguageMessage
    : public MessageBase<AddLanguageMessage, IAddLanguageMessage> {
public:
  AddLanguageMessage(const std::string &_value) : _value(_value) {}
  std::string GetValue() override { return _value; }

private:
  std::string _value;
};

} // namespace Vandrouka