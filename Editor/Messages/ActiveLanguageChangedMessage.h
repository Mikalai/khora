#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class ActiveLanguageChangedMessage
    : public MessageBase<ActiveLanguageChangedMessage,
                         IActiveLanguageChangedMessage> {
public:
  ActiveLanguageChangedMessage(std::string oldLanguage, std::string newLanguage)
      : _oldLanguage{oldLanguage}, _newLanguage{newLanguage} {}

  const std::string &GetOldLanguage() const override { return _oldLanguage; }
  const std::string &GetNewLanguage() const override { return _newLanguage; }

private:
  std::string _oldLanguage;
  std::string _newLanguage;
};

} // namespace Vandrouka