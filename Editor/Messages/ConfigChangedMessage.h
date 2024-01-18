#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class ConfigChangedMessage
    : public MessageBase<ConfigChangedMessage, IConfigChangedMessage> {
public:
  ConfigChangedMessage(Ref<IConfigEntry> cfg) : _config{cfg} {}

  Ref<IConfigEntry> GetConfig() const override { return _config; }

private:
  Ref<IConfigEntry> _config;
};

} // namespace Vandrouka