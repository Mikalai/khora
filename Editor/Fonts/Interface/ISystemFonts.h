#pragma once

#include <filesystem>
#include <string>
#include <vsg/all.h>

#include <Fundamental/Interface/IObserver.h>
#include <boost/asio/io_context.hpp>
#include <filesystem>

namespace Vandrouka::Fonts {

struct FontInfo {
  std::string FileName{};
  std::filesystem::path Path{};
  std::string Family{};
  std::string Style{};

  std::string GetDisplayName() const { return Family + " - " + Style; }

  bool IsValid() const {
    return !FileName.empty() && !Path.empty() && !Family.empty() &&
           !Style.empty();
  }
};

class ISystemFonts : public Fundamental::IReferenced {
public:
  virtual void Execute(Ref<IMessage> cmd) = 0;
};

} // namespace Vandrouka::Fonts

DECLARE_CID(Fonts, SystemFonts, 0xb8, 0xd3, 0x29, 0x27, 0xc6, 0x57, 0x41, 0x37,
            0xa8, 0x6c, 0x19, 0xf8, 0x28, 0xa0, 0x73, 0xf8);

DECLARE_IID(Vandrouka::Fonts::ISystemFonts, 0xa1, 0x15, 0x49, 0x54, 0xc8, 0xb9,
            0x4b, 0x80, 0x86, 0x2f, 0xc0, 0x6d, 0xf6, 0xa5, 0x2d, 0xe9);
