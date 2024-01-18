#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class RemoveLanguageMessage
    : public MessageBase<RemoveLanguageMessage, IRemoveLanguageMessage> {

public:
  RemoveLanguageMessage(const std::string &_value) : _value(_value) {}
  std::string GetValue() override { return _value; }

private:
  std::string _value;
};

class RenameLanguageMessage
    : public MessageBase<RenameLanguageMessage, IRenameLanguageMessage> {
public:
  RenameLanguageMessage(const std::string &_oldValue,
                        const std::string &_newValue)
      : _oldValue(_oldValue), _newValue(_newValue) {}

  std::string GetOldValue() override { return _oldValue; }
  std::string GetNewValue() override { return _newValue; }

private:
  std::string _oldValue;
  std::string _newValue;
};

} // namespace Vandrouka