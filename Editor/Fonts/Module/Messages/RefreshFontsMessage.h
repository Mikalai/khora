#pragma once

#include <Fonts/Interface/Messages/IRefreshFontsMessage.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::Fonts::Private::Messages {

class RefreshFontsMessage
    : public Fundamental::Private::MessageBase<
          RefreshFontsMessage, Fonts::Messages::IRefreshFontsMessage> {
public:
  RefreshFontsMessage(bool force) : _force{force} {}
  bool GetForce() const override { return _force; }

private:
  bool _force;
};

} // namespace Vandrouka::Fonts::Private::Messages
