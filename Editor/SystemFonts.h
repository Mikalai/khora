#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/thread.hpp>
#include "UI/EditorMainWindow.h"
#include "Observer.h"

class SystemFonts;
using SystemFontsPtr = std::shared_ptr<SystemFonts>;

struct FontInfo {
    std::string Name;
    std::filesystem::path Path;    
};

class ISystemFontsObserver {
public:
    virtual ~ISystemFontsObserver() {}

    virtual void Execute(const LogNotification& log) = 0;

    struct RefreshComplete {
        std::vector<FontInfo> Fonts;
    };

    virtual void Execute(const RefreshComplete& cmd) = 0;

    struct FontCompiled {
        vsg::ref_ptr<vsg::Font> Font;
        vsg::ref_ptr<vsg::Node> Root;
    };

    virtual void Execute(const FontCompiled& cmd) = 0;
};


class SystemFontsObserverAdapter : public ISystemFontsObserver {
public:
    SystemFontsObserverAdapter(ISystemFontsObserver& other)
        : _other{ other }
    {
    }

    void Execute(const LogNotification& cmd) override { _other.Execute(cmd); }
    void Execute(const RefreshComplete& cmd) override { _other.Execute(cmd); }
    void Execute(const FontCompiled& cmd) override { _other.Execute(cmd); }

private:
    ISystemFontsObserver& _other;
};

class ISystemFonts {
public:
    virtual ~ISystemFonts() {}
    
    [[nodiscard]]
    virtual SubscriptionPtr Subscribe(std::shared_ptr<ISystemFontsObserver> observer) = 0;
    virtual std::shared_ptr<AsyncQueue> GetSyncContext() = 0;

    struct Refresh {
        bool Force{false};
    };

    virtual void Execute(const Refresh& cmd) = 0;

    struct CompileFont {
        std::filesystem::path Path;
    };

    virtual void Execute(const CompileFont& cmd) = 0;
};

class SystemFonts final : public Observable<SystemFonts, ISystemFontsObserver, ISystemFonts> {    
    using Base = Observable<SystemFonts, ISystemFontsObserver, ISystemFonts>;
    friend class Observable<SystemFonts, ISystemFontsObserver, ISystemFonts>;

protected:
    SystemFonts(boost::asio::io_context& ctx);

public:

    using Callback = std::function<void(SystemFontsPtr)>;
    
    void Execute(const Refresh& cmd) override;
    void Execute(const CompileFont& cmd) override;
private:

    void RefreshInternal();
    std::vector<FontInfo> ReadFontPaths(std::filesystem::path fonts);
    std::filesystem::path GetFontFile();

private:
    std::vector<FontInfo> _allFontFiles;
    vsg::ref_ptr<vsg::Options> _options;
};
