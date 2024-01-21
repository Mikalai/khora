#ifdef __linux__
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#endif

#ifdef _WIN32
#define NOMINMAX
#include <Shlobj.h>
#include <Windows.h>
#endif

#include <ft2build.h>
#include <vsg/all.h>
#include <vsgXchange/all.h>

#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/dll.hpp>
#include <ranges>
#include FT_FREETYPE_H

#include <Fonts/Interface/ISystemFonts.h>
#include <Fonts/Module/Processors/CompileFontsProcessor.h>
#include <Fonts/Module/Processors/RefreshFontsProcessor.h>
#include <Fundamental/Module/MessageProcessor.h>
#include <Fundamental/Module/Observer.h>

#include "Application.h"
#include "ISystemFontsPrivate.h"
#include "IoContext.h"
#include "UI/EditorMainWindow.h"
#include "UI/UICommon.h"

namespace Vandrouka::Fonts::Private {

/*
 * Once again I started writing code without thinking and got troubles.
 * Let's step back and identify what do I want. So, I like idea of async
 * queues and message passing. And I want extract common code related to
 * message processing. I see that there are at least two components that
 * process messages: SystemFonts, DataModel. They are both message processors.
 * Are they observers? No, not exactly. They process messages, but this
 * is specific messages to this components that is why observer is not what they
 * are in such case. They are message sinks at least or channels. How to name
 * this? Besides this I want to split this components into a set of
 * IMessageProcessors. Each implementation of IMessageProcessor provides a piece
 * of functionality that based on the incoming message performs modification of
 * the state and if needed replies to the provided sink if needed. Message
 * processor supposed to be stateless. This is a pure function in the form of
 * the class. Is it correct to say that SystemFonts and DataModel is the same
 * entity and the only difference is a set of processors used by this objects?
 * Not entirely. Not only a set of processors, but also a state that can be
 * accepted by this processors. But yes. In general, SystemFonts and DataModel
 * should be the same thing from the point of view how message processing is
 * implemented.
 */

class SystemFonts final
    : public Fundamental::Private::ObservableBase<
          SystemFonts, ISystemFontsPrivate, IMessageOutput> {
public:
  using Interfaces =
      Fundamental::Private::QueryInterfaces<SystemFonts, ISystemFontsPrivate,
                                            ISystemFonts, IMessageOutput,
                                            IObservable, IReferenced>;

  SystemFonts() {

    _processor =
        new Fundamental::Private::AggregatedProcessorAsync{GetSyncContext()};
    _processor->AddProcessor(new Processors::RefreshFontsProcessor());
    _processor->AddProcessor(new Processors::CompileFontsProcessor());

    _options = vsg::Options::create(vsgXchange::all::create());
    _options->sharedObjects = vsg::SharedObjects::create();

    auto error = FT_Init_FreeType(&_library);
    _supportsFT = error == FT_Err_Ok;

    _allFontFiles = ReadFontPaths(GetFontFile());
  }

  std::optional<CompiledFont> FindCompiledFont(std::string_view name) override {
    if (auto it = _compiledFontsCache.find(std::string(name));
        it != _compiledFontsCache.end()) {
      return it->second;
    }
    return {};
  }

  std::optional<FontInfo> FindFontFile(std::string_view name) override {
    if (auto it = this->_allFontFiles.find(std::string(name));
        it != this->_allFontFiles.end()) {
      return it->second;
    }
    return {};
  }

  vsg::ref_ptr<vsg::Options> GetOptions() override { return _options; }

  void CacheCompiledFont(std::string_view name, CompiledFont &&font) override {
    _compiledFontsCache[std::string(name)] = std::move(font);
  }

  bool HasFonts() const override { return !_allFontFiles.empty(); }

  std::vector<FontInfo> GetFonts() override {
    auto value = std::views::values(_allFontFiles);
    std::vector<FontInfo> allFonts{value.begin(), value.end()};
    return allFonts;
  }

  void SubmitMessage(Ref<IMessage> msg) override { RaiseMessage(msg); }
  void SubmitError(Ref<IError> msg) override { RaiseError(msg); }

  void Execute(Ref<IMessage> cmd) override {
    _processor->Process(static_cast<ISystemFonts *>(this), cmd,
                        static_cast<IMessageOutput *>(this));
  }

  FontInfo GetFontInfo(std::filesystem::path path) {
    if (!_supportsFT) {
      return {};
    }

    FontInfo info{.FileName = path.filename().string(), .Path = path};

    FT_Face face;

    auto error = FT_New_Face(_library, path.string().c_str(), 0, &face);

    if (error == FT_Err_Unknown_File_Format) {
      return {};
    } else if (error) {
      return {};
    }

    if (face->family_name && face->style_name) {
      info.Family = face->family_name;
      info.Style = face->style_name;
    }

    FT_Done_Face(face);

    return info;
  }

  std::map<std::string, FontInfo> ReadFontPaths(std::filesystem::path fonts) {
    std::map<std::string, FontInfo> allFonts;

    std::ifstream stream(fonts, std::ios::binary);
    if (stream.is_open()) {
      std::string text((std::istreambuf_iterator<char>(stream)),
                       std::istreambuf_iterator<char>());
      std::vector<std::string> lines;
      boost::split(lines, text, boost::algorithm::is_any_of("\n\r"));

      for (auto entry : lines) {
        if (entry.empty())
          continue;
        if (boost::ends_with(entry, ".ttf")) {
          std::filesystem::path path{entry};
          if (auto info = GetFontInfo(path); info.IsValid()) {
            allFonts[info.GetDisplayName()] = info;
          }
        }
      }
    }

    return allFonts;
  }

  std::filesystem::path GetFontFile() {
#ifdef __linux__

    struct passwd *pw = getpwuid(getuid());
    std::filesystem::path homedir = pw->pw_dir;

#else
    WCHAR path[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) {
      return ".";
    }

    std::filesystem::path homedir = path;
#endif

    auto dir = homedir / ".khora_editor";

    if (!std::filesystem::exists(dir)) {
      std::filesystem::create_directory(dir);
    }

    return dir / "fonts.txt";
  }

  void RefreshInternal() override {
    auto fonts = GetFontFile();

#ifdef __linux__
    system(("find / -iname \"*.ttf\" >> " + fonts.string()).c_str());
#elif _WIN32
    std::vector<std::filesystem::path> folders;
    WCHAR path[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_FONTS, NULL, 0, path))) {
      return;
    }

    folders.push_back(path);

    if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) {
      return;
    }

    folders.push_back(std::filesystem::path(path) / "AppData" / "Local" /
                      "Microsoft" / "Windows" / "Fonts");

    std::ofstream stream(fonts);
    for (auto path : folders) {
      for (const auto &entry : std::filesystem::directory_iterator(path)) {
        stream << entry.path().string() << std::endl;
      }
    }

#else
    static_assert(false, "Platform doesn't support fonts");
#endif

    _allFontFiles = ReadFontPaths(fonts);
  }

  Ref<Fundamental::IAggregatedProcessor> _processor;
  std::map<std::string, FontInfo> _allFontFiles;
  std::unordered_map<std::string, CompiledFont> _compiledFontsCache;
  vsg::ref_ptr<vsg::Options> _options;
  FT_Library _library;
  bool _supportsFT{false};
};

} // namespace Vandrouka::Fonts::Private

namespace Vandrouka::Factory {

IReferenced *CreateSystemFonts() {
  return static_cast<Fonts::ISystemFonts *>(new Fonts::Private::SystemFonts());
}

} // namespace Vandrouka::Factory
