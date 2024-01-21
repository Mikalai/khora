#pragma once

#include <optional>
#include <vsg/all.h>

#include <Fonts/Interface/ISystemFonts.h>

namespace Vandrouka::Fonts::Private {

struct CompiledFont {
  vsg::ref_ptr<vsg::Font> Font;
  vsg::ref_ptr<vsg::Node> Root;
};

class ISystemFontsPrivate : public ISystemFonts {
public:
  virtual bool HasFonts() const = 0;
  virtual void RefreshInternal() = 0;
  virtual std::vector<FontInfo> GetFonts() = 0;
  virtual std::optional<CompiledFont>
  FindCompiledFont(std::string_view name) = 0;
  virtual std::optional<FontInfo> FindFontFile(std::string_view name) = 0;
  virtual vsg::ref_ptr<vsg::Options> GetOptions() = 0;
  virtual void CacheCompiledFont(std::string_view name,
                                 CompiledFont &&font) = 0;
};

} // namespace Vandrouka::Fonts::Private

DECLARE_IID(Vandrouka::Fonts::Private::ISystemFontsPrivate, 0x64, 0x18, 0xbd,
            0x16, 0x48, 0x1c, 0x4d, 0x73, 0xb5, 0x96, 0xf7, 0x93, 0x7f, 0xc6,
            0xe6, 0x3f);
