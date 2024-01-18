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

#include "Application.h"
#include "ISystemFonts.h"
#include "IoContext.h"
#include "MessageProcessor.h"
#include "Observer.h"
#include "UI/EditorMainWindow.h"
#include "UI/UICommon.h"

namespace Vandrouka {

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

template <> struct GetIID<ISystemFontsPrivate> {
  static constexpr InterfaceId Id = {{0x64, 0x18, 0xbd, 0x16, 0x48, 0x1c, 0x4d,
                                      0x73, 0xb5, 0x96, 0xf7, 0x93, 0x7f, 0xc6,
                                      0xe6, 0x3f}};
};

class FontsRefreshCompletedMessage
    : public MessageBase<FontsRefreshCompletedMessage,
                         IFontsRefreshCompletedMessage> {
public:
  FontsRefreshCompletedMessage(std::vector<FontInfo> &&fonts)
      : _allFonts{std::move(fonts)} {}

  const std::vector<FontInfo> &GetFonts() override { return _allFonts; }

private:
  std::vector<FontInfo> _allFonts;
};

class RefreshFontsProcessor
    : public MessageProcessorBase<RefreshFontsProcessor, ISystemFontsPrivate,
                                  IRefreshFontsMessage> {

public:
  void ProcessMessage(Ref<ISystemFontsPrivate> state,
                      Ref<IRefreshFontsMessage> cmd, Ref<IMessageOutput> sink) {
    if (cmd->GetForce() || !state->HasFonts()) {
      state->RefreshInternal();
    }

    sink->SubmitMessage(new FontsRefreshCompletedMessage{state->GetFonts()});
  }
};

class FontCompiledMessage
    : public MessageBase<FontCompiledMessage, IFontCompiledMessage> {
public:
  FontCompiledMessage(std::string name, vsg::ref_ptr<vsg::Font> font,
                      vsg::ref_ptr<vsg::Node> node, Ref<IReferenced> state)
      : _name{name}, _font{font}, _node{node}, _state{state} {}

  const std::string &GetDisplayName() const override { return _name; }
  vsg::ref_ptr<vsg::Font> GetFont() const override { return _font; }
  vsg::ref_ptr<vsg::Node> GetRoot() const override { return _node; }
  Ref<IReferenced> GetState() const override { return _state; }

private:
  std::string _name;
  vsg::ref_ptr<vsg::Font> _font;
  vsg::ref_ptr<vsg::Node> _node;
  Ref<IReferenced> _state;
};

class CompileFontsProcessor
    : public MessageProcessorBase<CompileFontsProcessor, ISystemFontsPrivate,
                                  ICompileFontMessage> {

public:
  void ReportMessage(Ref<IMessage> msg, Ref<IReferenced> observer,
                     Ref<IMessageOutput> output) {
    output->SubmitMessage(msg);
  }

  void ProcessMessage(Ref<ISystemFontsPrivate> state,
                      Ref<ICompileFontMessage> cmd, Ref<IMessageOutput> sink) {

    LongOperationScope scope{
        *sink.Get(), &IMessageOutput::SubmitMessage,
        LongOperation{.Name = "Compile font: " + cmd->GetDisplayName()}};

    if (auto fnt = state->FindCompiledFont(cmd->GetDisplayName()); fnt) {
      ReportMessage(new FontCompiledMessage{
          cmd->GetDisplayName(), fnt->Font, fnt->Root, cmd->GetState()}, cmd->GetState(), sink);
      return;
    }

    if (auto fnt = state->FindFontFile(cmd->GetDisplayName()); !fnt) {
      sink->SubmitError(new GenericError<std::string>{
          LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND, cmd->GetDisplayName()});
      ReportMessage(
          new FontCompiledMessage{
              cmd->GetDisplayName(), {}, {}, cmd->GetState()},
          cmd->GetState(), sink);
      return;
    } else if (auto object = vsg::read(fnt->Path.string(), state->GetOptions());
               object) {
      if (auto font = object.cast<vsg::Font>(); font) {
        auto scenegraph = vsg::MatrixTransform::create();

        auto layout = vsg::StandardLayout::create();
        layout->position = vsg::vec3(0.0, 0.0, 0.0);
        layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
        layout->vertical = vsg::vec3(0.0, 1.0, 0.0);
        layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);

        std::set<uint32_t> characters;
        for (auto c : *(font->charmap)) {
          if (c != 0)
            characters.insert(c);
        }

        size_t num_glyphs = characters.size();
        size_t row_length = static_cast<size_t>(ceil(sqrt(float(num_glyphs))));

        if (row_length == 0) {
          sink->SubmitError(new GenericError{
              LOG_LEVEL_ERROR, LOG_FILE_LOAD_FAILED, cmd->GetDisplayName()});
          return;
        }

        size_t num_rows = num_glyphs / row_length;
        if ((num_glyphs % num_rows) != 0)
          ++num_rows;

        // use an uintArray to store the text string as the full
        // font charcodes can go up to very large values.
        auto text_string = vsg::uintArray::create(num_glyphs + num_rows - 1);
        auto text_itr = text_string->begin();

        size_t i = 0;
        size_t column = 0;

        for (auto c : characters) {
          ++i;
          ++column;

          (*text_itr++) = c;

          if (column >= row_length) {
            (*text_itr++) = '\n';
            column = 0;
          }
        }

        auto text = vsg::Text::create();
        text->font = font;
        text->layout = layout;
        text->text = text_string;
        text->setup(0, state->GetOptions());

        scenegraph->addChild(text);

        state->CacheCompiledFont(cmd->GetDisplayName(),
                                 {.Font = font, .Root = scenegraph});

        ReportMessage(new FontCompiledMessage{cmd->GetDisplayName(), font,
                                              scenegraph, cmd->GetState()},
                      cmd->GetState(), sink);

      } else {
        sink->SubmitMessage(new GenericError(
            LOG_LEVEL_ERROR, LOG_FILE_LOAD_FAILED, cmd->GetDisplayName()));
        ReportMessage(
            new FontCompiledMessage{
                cmd->GetDisplayName(), {}, {}, cmd->GetState()},
            cmd->GetState(), sink);
      }
    } else {
      sink->SubmitError(new GenericError(LOG_LEVEL_ERROR, LOG_FILE_LOAD_FAILED,
                                         cmd->GetDisplayName()));
      ReportMessage(
          new FontCompiledMessage{
              cmd->GetDisplayName(), {}, {}, cmd->GetState()},
          cmd->GetState(), sink);
    }
  }
};

class SystemFonts final
    : public ObservableBase<SystemFonts, ISystemFontsPrivate, IMessageOutput> {
public:
  using Interfaces =
      QueryInterfaces<SystemFonts, ISystemFontsPrivate, ISystemFonts,
                      IMessageOutput, IObservable, IReferenced>;

  SystemFonts() {

    static_assert(std::is_same_v<
                  AggregatedProcessorAsync::Interfaces,
                  Private::QueryInterfacesStruct<
                      AggregatedProcessor, IAggregatedProcessor,
                      IAggregatedProcessor, IMessageProcessor, IReferenced>>);

    _processor = new AggregatedProcessorAsync{GetSyncContext()};
    _processor->AddProcessor(new RefreshFontsProcessor());
    _processor->AddProcessor(new CompileFontsProcessor());

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

    folders.push_back(std::filesystem::path(path) /
                      "AppData" / "Local" / "Microsoft" / "Windows" / "Fonts");

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

  Ref<IAggregatedProcessor> _processor;
  std::map<std::string, FontInfo> _allFontFiles;
  std::unordered_map<std::string, CompiledFont> _compiledFontsCache;
  vsg::ref_ptr<vsg::Options> _options;
  FT_Library _library;
  bool _supportsFT{false};
};

IReferenced *CreateSystemFonts() {
  return static_cast<ISystemFonts *>(new SystemFonts());
}

} // namespace Vandrouka
//
//class SystemFonts final
//    : public Observable<SystemFonts, ISystemFontsObserver, ISystemFonts> {
//  using Base = Observable<SystemFonts, ISystemFontsObserver, ISystemFonts>;
//  friend class Observable<SystemFonts, ISystemFontsObserver, ISystemFonts>;
//
//protected:
//  SystemFonts(std::shared_ptr<boost::asio::io_context> ctx);
//
//public:
//  virtual ~SystemFonts() {
//    if (_library) {
//      FT_Done_FreeType(_library);
//      _library = {};
//    }
//  }
//
//  using Callback = std::function<void(SystemFontsPtr)>;
//
//  void Execute(const Refresh &cmd) override;
//  void Execute(const CompileFont &cmd) override;
//
//private:
//  void RefreshInternal();
//  std::map<std::string, FontInfo> ReadFontPaths(std::filesystem::path fonts);
//  FontInfo GetFontInfo(std::filesystem::path path);
//  std::filesystem::path GetFontFile();
//
//private:
//  std::map<std::string, FontInfo> _allFontFiles;
//
//  struct CompiledFont {
//    vsg::ref_ptr<vsg::Font> Font;
//    vsg::ref_ptr<vsg::Node> Root;
//  };
//
//  std::unordered_map<std::string, CompiledFont> _compiledFontsCache;
//  vsg::ref_ptr<vsg::Options> _options;
//  FT_Library _library;
//  bool _supportsFT{false};
//};
//
//SystemFonts::SystemFonts(std::shared_ptr<boost::asio::io_context> ctx)
//    : Base{ctx} {
//  _options = vsg::Options::create(vsgXchange::all::create());
//  _options->sharedObjects = vsg::SharedObjects::create();
//
//  auto error = FT_Init_FreeType(&_library);
//  _supportsFT = error == FT_Err_Ok;
//
//  _allFontFiles = ReadFontPaths(GetFontFile());
//}
//
//void SystemFonts::Execute(const Refresh &cmd) {
//  GetSyncContext()->Enqueue([this, cmd]() {
//    if (cmd.Force || _allFontFiles.empty()) {
//      RefreshInternal();
//    }
//
//    auto value = std::views::values(_allFontFiles);
//    std::vector<FontInfo> allFonts{value.begin(), value.end()};
//    Notify(ISystemFontsObserver::RefreshComplete{.Fonts = allFonts});
//  });
//}
//
//void SystemFonts::Execute(const CompileFont &cmd) {
//  GetSyncContext()->Enqueue([this, cmd]() {
//    LongOperationScope scope{
//        *this, &SystemFonts::Notify<LongOperationStarted>,
//        &SystemFonts::Notify<LongOperationEnded>,
//        LongOperation{.Name = "Compile font: " + cmd.DisplayName}};
//
//    if (auto it = _compiledFontsCache.find(cmd.DisplayName);
//        it != _compiledFontsCache.end()) {
//      Notify(ISystemFontsObserver::FontCompiled{.DisplayName = cmd.DisplayName,
//                                                .Font = it->second.Font,
//                                                .Root = it->second.Root,
//                                                .State = cmd.State});
//      return;
//    }
//
//    if (auto it = this->_allFontFiles.find(cmd.DisplayName);
//        it == this->_allFontFiles.end()) {
//      Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.DisplayName));
//      return;
//    } else if (auto object = vsg::read(it->second.Path.string(), _options);
//               object) {
//      if (auto font = object.cast<vsg::Font>(); font) {
//        auto scenegraph = vsg::MatrixTransform::create();
//
//        auto layout = vsg::StandardLayout::create();
//        layout->position = vsg::vec3(0.0, 0.0, 0.0);
//        layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
//        layout->vertical = vsg::vec3(0.0, 1.0, 0.0);
//        layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);
//
//        std::set<uint32_t> characters;
//        for (auto c : *(font->charmap)) {
//          if (c != 0)
//            characters.insert(c);
//        }
//
//        size_t num_glyphs = characters.size();
//        size_t row_length = static_cast<size_t>(ceil(sqrt(float(num_glyphs))));
//
//        if (row_length == 0) {
//          Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.DisplayName));
//          return;
//        }
//
//        size_t num_rows = num_glyphs / row_length;
//        if ((num_glyphs % num_rows) != 0)
//          ++num_rows;
//
//        // use an uintArray to store the text string as the full font
//        // charcodes can go up to very large values.
//        auto text_string = vsg::uintArray::create(num_glyphs + num_rows - 1);
//        auto text_itr = text_string->begin();
//
//        size_t i = 0;
//        size_t column = 0;
//
//        for (auto c : characters) {
//          ++i;
//          ++column;
//
//          (*text_itr++) = c;
//
//          if (column >= row_length) {
//            (*text_itr++) = '\n';
//            column = 0;
//          }
//        }
//
//        auto text = vsg::Text::create();
//        text->font = font;
//        text->layout = layout;
//        text->text = text_string;
//        text->setup(0, _options);
//
//        scenegraph->addChild(text);
//
//        _compiledFontsCache[cmd.DisplayName] = {.Font = font,
//                                                .Root = scenegraph};
//
//        Notify(
//            ISystemFontsObserver::FontCompiled{.DisplayName = cmd.DisplayName,
//                                               .Font = font,
//                                               .Root = scenegraph,
//                                               .State = cmd.State});
//      } else {
//        Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.DisplayName));
//      }
//    } else {
//      Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.DisplayName));
//    }
//  });
//}
//
//FontInfo SystemFonts::GetFontInfo(std::filesystem::path path) {
//  if (!_supportsFT) {
//    return {};
//  }
//
//  FontInfo info{.FileName = path.filename().string(), .Path = path};
//
//  FT_Face face;
//
//  auto error = FT_New_Face(_library, path.string().c_str(), 0, &face);
//
//  if (error == FT_Err_Unknown_File_Format) {
//    return {};
//  } else if (error) {
//    return {};
//  }
//
//  if (face->family_name && face->style_name) {
//    info.Family = face->family_name;
//    info.Style = face->style_name;
//  }
//
//  FT_Done_Face(face);
//
//  return info;
//}
//
//std::map<std::string, FontInfo>
//SystemFonts::ReadFontPaths(std::filesystem::path fonts) {
//  std::map<std::string, FontInfo> allFonts;
//
//  std::ifstream stream(fonts, std::ios::binary);
//  if (stream.is_open()) {
//    std::string text((std::istreambuf_iterator<char>(stream)),
//                     std::istreambuf_iterator<char>());
//    std::vector<std::string> lines;
//    boost::split(lines, text, boost::algorithm::is_any_of("\n\r"));
//
//    for (auto entry : lines) {
//      if (entry.empty())
//        continue;
//      if (boost::ends_with(entry, ".ttf")) {
//        std::filesystem::path path{entry};
//        if (auto info = GetFontInfo(path); info.IsValid()) {
//          allFonts[info.GetDisplayName()] = info;
//        }
//      }
//    }
//  }
//
//  return allFonts;
//}
//
//std::filesystem::path SystemFonts::GetFontFile() {
//#ifdef __linux__
//
//  struct passwd *pw = getpwuid(getuid());
//  std::filesystem::path homedir = pw->pw_dir;
//
//#else
//  WCHAR path[MAX_PATH];
//  if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) {
//    return ".";
//  }
//
//  std::filesystem::path homedir = path;
//#endif
//
//  auto dir = homedir / ".khora_editor";
//
//  if (!std::filesystem::exists(dir)) {
//    std::filesystem::create_directory(dir);
//  }
//
//  return dir / "fonts.txt";
//}
//
//void SystemFonts::RefreshInternal() {
//  auto fonts = GetFontFile();
//
//#ifdef __linux__
//  system(("find / -iname \"*.ttf\" >> " + fonts.string()).c_str());
//#elif _WIN32
//  WCHAR path[MAX_PATH];
//  if (FAILED(SHGetFolderPathW(NULL, CSIDL_FONTS, NULL, 0, path))) {
//    return;
//  }
//
//  {
//    std::ofstream stream(fonts);
//
//    for (const auto &entry : std::filesystem::directory_iterator(path)) {
//      stream << entry.path() << std::endl;
//    }
//  }
//
//#else
//  static_assert(false, "Platform doesn't support fonts");
//#endif
//
//  _allFontFiles = ReadFontPaths(fonts);
//}
//
//std::shared_ptr<ISystemFonts>
//ISystemFonts::Create(std::shared_ptr<boost::asio::io_context> ctx) {
//  return SystemFonts::Create(ctx);
//}
