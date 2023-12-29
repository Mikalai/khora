#pragma once

#include <vsg/all.h>

#include <boost/asio/io_context.hpp>
#include <filesystem>

#include "LongOperationNotification.h"
#include "Observer.h"

class ISystemFonts;
using SystemFontsPtr = std::shared_ptr<ISystemFonts>;

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

class ISystemFontsObserver {
public:
  virtual ~ISystemFontsObserver() {}

  virtual void Execute(const LogNotification &log) = 0;

  struct RefreshComplete {
    std::vector<FontInfo> Fonts;
  };

  virtual void Execute(const RefreshComplete &cmd) = 0;

  struct FontCompiled {
    std::string DisplayName;
    vsg::ref_ptr<vsg::Font> Font;
    vsg::ref_ptr<vsg::Node> Root;
    std::shared_ptr<CustomState> State;
  };

  virtual void Execute(const FontCompiled &cmd) = 0;

  virtual void Execute(const LongOperationStarted &cmd) = 0;
  virtual void Execute(const LongOperationEnded &cmd) = 0;
};

class SystemFontsObserverAdapter : public ISystemFontsObserver {
public:
  SystemFontsObserverAdapter(ISystemFontsObserver &other) : _other{other} {}

  void Execute(const LogNotification &cmd) override { _other.Execute(cmd); }
  void Execute(const RefreshComplete &cmd) override { _other.Execute(cmd); }
  void Execute(const FontCompiled &cmd) override { _other.Execute(cmd); }
  void Execute(const LongOperationStarted &cmd) override {
    _other.Execute(cmd);
  }
  void Execute(const LongOperationEnded &cmd) override { _other.Execute(cmd); }

private:
  ISystemFontsObserver &_other;
};

class ISystemFonts {
public:
  virtual ~ISystemFonts() {}

  [[nodiscard]] virtual SubscriptionPtr
  Subscribe(std::shared_ptr<ISystemFontsObserver> observer) = 0;
  virtual std::shared_ptr<AsyncQueue> GetSyncContext() = 0;

  struct Refresh {
    bool Force{false};
  };

  virtual void Execute(const Refresh &cmd) = 0;

  struct CompileFont {
    std::string DisplayName;
    std::shared_ptr<CustomState> State;
  };

  virtual void Execute(const CompileFont &cmd) = 0;

  static std::shared_ptr<ISystemFonts>
  Create(std::shared_ptr<boost::asio::io_context> ctx);
};
