#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class SetActiveLanguageMessage
    : public MessageBase<SetActiveLanguageMessage, ISetActiveLanguageMessage> {
public:
  SetActiveLanguageMessage(const std::string &_value) : _value(_value) {}

  const std::string &GetLanguage() const override { return _value; }

private:
  std::string _value;
};

} // namespace Vandrouka