#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <boost/dll.hpp>

#include <vsg/all.h>
#include <vsgXchange/all.h>

#include "Application.h"
#include "UI/EditorMainWindow.h"
#include "UI/UICommon.h"

SystemFonts::SystemFonts(boost::asio::io_context& ctx)
    : Base{ ctx }
{
    _options = vsg::Options::create(vsgXchange::all::create());
    _options->sharedObjects = vsg::SharedObjects::create();

    _allFontFiles = ReadFontPaths(GetFontFile());
}

void SystemFonts::Execute(const Refresh& cmd)
{
    GetSyncContext()->Enqueue([this, cmd]() {

        if (cmd.Force || _allFontFiles.empty()) {
            RefreshInternal();
        }

        Notify(ISystemFontsObserver::RefreshComplete{ .Fonts = _allFontFiles });
        });
}

void SystemFonts::Execute(const CompileFont& cmd) {

    GetSyncContext()->Enqueue([this, cmd]() {
        if (auto object = vsg::read(cmd.Path.string(), _options); object) {
            if (auto font = object.cast<vsg::Font>(); font) {
                auto scenegraph = vsg::MatrixTransform::create();

                auto layout = vsg::StandardLayout::create();
                layout->position = vsg::vec3(0.0, 0.0, 0.0);
                layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
                layout->vertical = vsg::vec3(0.0, 0.0, 1.0);
                layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);

                std::set<uint32_t> characters;
                for (auto c : *(font->charmap))
                {
                    if (c != 0) characters.insert(c);
                }

                size_t num_glyphs = characters.size();
                size_t row_length = static_cast<size_t>(ceil(sqrt(float(num_glyphs))));
                size_t num_rows = num_glyphs / row_length;
                if ((num_glyphs % num_rows) != 0) ++num_rows;

                // use an uintArray to store the text string as the full font charcodes can go up to very large values.
                auto text_string = vsg::uintArray::create(num_glyphs + num_rows - 1);
                auto text_itr = text_string->begin();

                size_t i = 0;
                size_t column = 0;

                for (auto c : characters)
                {
                    ++i;
                    ++column;

                    (*text_itr++) = c;

                    if (column >= row_length)
                    {
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

                Notify(ISystemFontsObserver::FontCompiled{ .Font = font, .Root = scenegraph });
            }
            else {
                Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.Path.string()));
            }
        }
        else {
            Notify(LogError(LOG_FILE_LOAD_FAILED, cmd.Path.string()));
        }
        });
}

std::vector<FontInfo> SystemFonts::ReadFontPaths(std::filesystem::path fonts) {
    std::vector<FontInfo> allFonts;

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
                std::filesystem::path path{ entry };
                allFonts.push_back(FontInfo{ .Name = path.filename(), .Path = path });
            }
        }
    }

    return allFonts;
}

std::filesystem::path SystemFonts::GetFontFile()
{
#ifdef __linux__

    struct passwd* pw = getpwuid(getuid());
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
