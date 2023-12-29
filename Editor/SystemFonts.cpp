#ifdef __linux__
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
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
#include "UI/EditorMainWindow.h"
#include "UI/UICommon.h"

class SystemFonts final
    : public Observable<SystemFonts, ISystemFontsObserver, ISystemFonts> {
  using Base = Observable<SystemFonts, ISystemFontsObserver, ISystemFonts>;
  friend class Observable<SystemFonts, ISystemFontsObserver, ISystemFonts>;

protected:
  SystemFonts(std::shared_ptr<boost::asio::io_context> ctx);

public:
  virtual ~SystemFonts() {
    if (_library) {
      FT_Done_FreeType(_library);
      _library = {};
    }
  }

  using Callback = std::function<void(SystemFontsPtr)>;

  void Execute(const Refresh &cmd) override;
  void Execute(const CompileFont &cmd) override;

private:
  void RefreshInternal();
  std::map<std::string, FontInfo> ReadFontPaths(std::filesystem::path fonts);
  FontInfo GetFontInfo(std::filesystem::path path);
  std::filesystem::path GetFontFile();

private:
  std::map<std::string, FontInfo> _allFontFiles;

  struct CompiledFont {
    vsg::ref_ptr<vsg::Font> Font;
    vsg::ref_ptr<vsg::Node> Root;
  };

  std::unordered_map<std::string, CompiledFont> _compiledFontsCache;
  vsg::ref_ptr<vsg::Options> _options;
  FT_Library _library;
  bool _supportsFT{false};
};

SystemFonts::SystemFonts(std::shared_ptr<boost::asio::io_context> ctx)
    : Base{ctx} {
  _options = vsg::Options::create(vsgXchange::all::create());
  _options->sharedObjects = vsg::SharedObjects::create();

  auto error = FT_Init_FreeType(&_library);
  _supportsFT = error == FT_Err_Ok;

  _allFontFiles = ReadFontPaths(GetFontFile());
}

void SystemFonts::Execute(const Refresh &cmd) {
  GetSyncContext()->Enqueue([this, cmd]() {
    if (cmd.Force || _allFontFiles.empty()) {
      RefreshInternal();
    }

    auto value = std::views::values(_allFontFiles);
    std::vector<FontInfo> allFonts{value.begin(), value.end()};
    Notify(ISystemFontsObserver::RefreshComplete{.Fonts = allFonts});
  });
}

void SystemFonts::Execute(const CompileFont &cmd) {
  GetSyncContext()->Enqueue([this, cmd]() {
    LongOperationScope scope{
        *this, &SystemFonts::Notify<LongOperationStarted>,
        &SystemFonts::Notify<LongOperationEnded>,
        LongOperation{.Name = "Compile font: " + cmd.DisplayName}};

    if (auto it = _compiledFontsCache.find(cmd.DisplayName);
        it != _compiledFontsCache.end()) {
      Notify(ISystemFontsObserver::FontCompiled{.DisplayName = cmd.DisplayName,
                                                .Font = it->second.Font,
                                                .Root = it->second.Root,
                                                .State = cmd.State});
      return;
    }

    if (auto it = this->_allFontFiles.find(cmd.DisplayName);
        it == this->_allFontFiles.end()) {
      Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.DisplayName));
      return;
    } else if (auto object = vsg::read(it->second.Path.string(), _options);
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
          Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.DisplayName));
          return;
        }

        size_t num_rows = num_glyphs / row_length;
        if ((num_glyphs % num_rows) != 0)
          ++num_rows;

        // use an uintArray to store the text string as the full font
        // charcodes can go up to very large values.
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
        text->setup(0, _options);

        scenegraph->addChild(text);

        _compiledFontsCache[cmd.DisplayName] = {.Font = font,
                                                .Root = scenegraph};

        Notify(
            ISystemFontsObserver::FontCompiled{.DisplayName = cmd.DisplayName,
                                               .Font = font,
                                               .Root = scenegraph,
                                               .State = cmd.State});
      } else {
        Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.DisplayName));
      }
    } else {
      Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.DisplayName));
    }
  });
}

FontInfo SystemFonts::GetFontInfo(std::filesystem::path path) {
  if (!_supportsFT) {
    return {};
  }

  FontInfo info{.FileName = path.filename(), .Path = path};

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

std::map<std::string, FontInfo>
SystemFonts::ReadFontPaths(std::filesystem::path fonts) {
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

std::filesystem::path SystemFonts::GetFontFile() {
#ifdef __linux__

  struct passwd *pw = getpwuid(getuid());
  std::filesystem::path homedir = pw->pw_dir;
  auto dir = homedir / ".khora_editor";

  if (!std::filesystem::exists(dir)) {
    std::filesystem::create_directory(dir);
  }

  return dir / "fonts.txt";
#else
  static_assert(false && "Platform is not supported");
#endif
}

void SystemFonts::RefreshInternal() {
  auto fonts = GetFontFile();

#ifdef __linux__
  system(("find / -iname \"*.ttf\" >> " + fonts.string()).c_str());
#elif _WIN32
  static_assert(false, "Platform doesn't support fonts");
#else
  static_assert(false, "Platform doesn't support fonts");
#endif

  _allFontFiles = ReadFontPaths(fonts);
}

std::shared_ptr<ISystemFonts>
ISystemFonts::Create(std::shared_ptr<boost::asio::io_context> ctx) {
  return SystemFonts::Create(ctx);
}