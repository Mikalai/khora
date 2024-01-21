#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <Fonts/Module/ISystemFontsPrivate.h>
#include <Fonts/Interface/Messages/IFontsRefreshCompletedMessage.h>

namespace Vandrouka::Fonts::Private::Messages {

class FontsRefreshCompletedMessage
    : public Fundamental::Private::MessageBase<FontsRefreshCompletedMessage,
          Fonts::Messages::IFontsRefreshCompletedMessage> {
public:
  FontsRefreshCompletedMessage(std::vector<FontInfo> &&fonts)
      : _allFonts{std::move(fonts)} {}

  const std::vector<FontInfo> &GetFonts() override { return _allFonts; }

private:
  std::vector<FontInfo> _allFonts;
};

} // namespace Vandrouka
