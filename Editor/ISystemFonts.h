#pragma once

#include <filesystem>
#include <string>
#include <vsg/all.h>

#include "IObserver.h"
#include <boost/asio/io_context.hpp>
#include <filesystem>

namespace Vandrouka {

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

class SystemFonts;
template <> struct GetCID<SystemFonts> {
  static constexpr ClassId Id = {{0xb8, 0xd3, 0x29, 0x27, 0xc6, 0x57, 0x41,
                                  0x37, 0xa8, 0x6c, 0x19, 0xf8, 0x28, 0xa0,
                                  0x73, 0xf8}};
};

class ISystemFonts : public IReferenced {
public:
  struct Refresh {
    bool Force{false};
  };

  virtual void Execute(const Refresh &cmd) = 0;

  struct CompileFont {
    std::string DisplayName;
    Ref<IReferenced> State;
  };

  virtual void Execute(const CompileFont &cmd) = 0;
};

template <> struct GetIID<ISystemFonts> {
  static constexpr InterfaceId Id = {{0xa1, 0x15, 0x49, 0x54, 0xc8, 0xb9, 0x4b,
                                      0x80, 0x86, 0x2f, 0xc0, 0x6d, 0xf6, 0xa5,
                                      0x2d, 0xe9}};
};

class IFontsRefreshCompletedMessage : public IMessage {
public:
  virtual const std::vector<FontInfo> &GetFonts() = 0;
};

template <> struct GetIID<IFontsRefreshCompletedMessage> {
  static constexpr InterfaceId Id = {{0xff, 0x91, 0xd0, 0x59, 0x1b, 0x27, 0x49,
                                      0x4f, 0xaa, 0x57, 0x5a, 0x32, 0x53, 0xb0,
                                      0x38, 0xe0}};
};

class IFontCompiledMessage : public IMessage {
public:
  virtual const std::string &GetDisplayName() const = 0;
  virtual vsg::ref_ptr<vsg::Font> GetFont() const = 0;
  virtual vsg::ref_ptr<vsg::Node> GetRoot() const = 0;
  virtual Ref<IReferenced> GetState() const = 0;
};

template <> struct GetIID<IFontCompiledMessage> {
  static constexpr InterfaceId Id = {{0x19, 0x90, 0x20, 0x67, 0xd1, 0x23, 0x40,
                                      0x28, 0x96, 0x66, 0x49, 0xcd, 0xa4, 0x5c,
                                      0xe9, 0x1c}};
};

} // namespace Vandrouka
