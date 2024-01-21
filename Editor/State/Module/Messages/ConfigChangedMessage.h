#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <Catalog/Interface/IConfigEntry.h>
#include <State/Interface/Messages/IConfigChangedMessage.h>

namespace Vandrouka::State::Private::Messages {

class ConfigChangedMessage
    : public Fundamental::Private::MessageBase<ConfigChangedMessage,
                                               State::Messages::IConfigChangedMessage> {
public:
  ConfigChangedMessage(Ref<Catalog::IConfigEntry> cfg) : _config{cfg} {}

  Ref<Catalog::IConfigEntry> GetConfig() const override { return _config; }

private:
  Ref<Catalog::IConfigEntry> _config;
};

} // namespace Vandrouka