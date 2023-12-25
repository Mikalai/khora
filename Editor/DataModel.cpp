#include "DataModel.h"

#include <boost/algorithm/string.hpp>
#include <boost/asio/post.hpp>
#include <boost/dll.hpp>
#include <filesystem>
#include <iostream>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#include "../Render/WorldCompiler.h"
#include "ConfigEntry.h"
#include "GeometryEntry.h"
#include "GroupEntry.h"
#include "LocalizedEntry.h"
#include "MaterialEntry.h"
#include "Serializer.h"
#include "TransformEntry.h"

DataModel::DataModel(boost::asio::io_context& ctx)
    : Base{ ctx }
    , _ctx{ ctx } {
}

void DataModel::OnCreated() {
    CreateAxis();
    Execute(IDataModelEditor::ResetModelCommand{});
}

DataModel::~DataModel() {}

void DataModel::Execute(const ImportFileCommand& cmd) {
    DenyCompilation();

    boost::asio::post(_ctx, [this, cmd]() {
        auto importFile = [&]() {

            std::filesystem::path requestedPath = cmd.FilePath;
            auto newPath = cmd.ProjectPath / "Raw" / requestedPath.filename();

            if (!std::filesystem::equivalent(requestedPath.parent_path(), newPath)) {
                auto oldPath = requestedPath;
                if (oldPath.is_relative()) {
                    oldPath = cmd.ProjectPath / oldPath;
                }
                if (oldPath != newPath) {
                    std::error_code ec;
                    if (!std::filesystem::copy_file(oldPath, newPath, std::filesystem::copy_options::overwrite_existing, ec)) {
                        Notify(LogError(LOG_IO_ERROR, ec.message()));
                        return;
                    }
                }
                requestedPath = newPath;
            }

            if (requestedPath.is_relative()) {
                requestedPath = cmd.ProjectPath / requestedPath;
            }

            if (auto root = vsg::read_cast<vsg::Node>(requestedPath.native(),
                cmd.Options);
                root) {
                auto relPath =
                    std::filesystem::relative(requestedPath, cmd.ProjectPath);

                Notify(IDataModelObserver::CompileCommand{
                    .Object = root,
                    .OnComplete = [&](auto object, auto result) {} });

                auto packageName =
                    std::filesystem::path(relPath).filename().string();

                _queue->Enqueue([=]() {
                    _packagePreviewRoots[packageName] =
                        PackageInfo{ .Path = relPath, .Root = root };

                    WorldCompiler compiler;
                    root->accept(compiler);

                    for (auto& o : compiler.objects) {
                        std::string path = o.first;

                        if (auto tr = std::get<0>(o.second)
                            .cast<vsg::MatrixTransform>();
                            tr) {
                            _dir->Add(
                                { ROOT_PACKAGES + "/" + packageName + "/" +
                                 PACKAGE_ENTRY_TRANSFORMS + "/" + o.first },
                                std::make_shared<TransformPackageEntry>(tr));

                            for (auto child : tr->children) {
                                if (auto m = child.cast<vsg::StateGroup>(); m) {
                                    _dir->Add(
                                        { ROOT_PACKAGES + "/" + packageName +
                                         "/" + PACKAGE_ENTRY_MATERIALS + "/" +
                                         o.first },
                                        std::make_shared<MaterialPackageEntry>(
                                            m));
                                }
                            }
                        }
                        if (auto tr = std::get<0>(o.second)
                            .cast<vsg::VertexIndexDraw>();
                            tr) {
                            _dir->Add(
                                { ROOT_PACKAGES + "/" + packageName + "/" +
                                 PACKAGE_ENTRY_GEOMETRIES + "/" + path },
                                std::make_shared<GeometryPackageEntry>(tr));
                        }
                        if (auto tr =
                            std::get<0>(o.second).cast<vsg::StateGroup>();
                            tr) {
                            _dir->Add(
                                { ROOT_PACKAGES + "/" + packageName + "/" +
                                 PACKAGE_ENTRY_MATERIALS + "/" + path },
                                std::make_shared<MaterialPackageEntry>(tr));
                        }
                    }
                    });
            }
            };

        importFile();
        AllowCompilation();
        });
}


void DataModel::Execute(const ResetModelCommand& cmd) {
    _queue->Enqueue([=]() {
        _dir = std::make_shared<GroupEntry>();
        _dir->AddObserver(Self());
        _dir->Add({ ROOT_CONFIG }, std::make_shared<ConfigEntry>());
        _packagePreviewRoots.clear();
        Notify(IDataModelObserver::ModelResetNotification{});
        Notify(IDataModelObserver::ConfigNotification{
            .Config = std::static_pointer_cast<ConfigEntry>(
                GetConfig()->CreateView(_queue)) });
        });
}

void DataModel::OnPropertyChanged(std::shared_ptr<Entry> sender,
    std::string_view name) {
    Notify(IDataModelObserver::EntryPropertyChangedNotification{
        .ChangedEntry = sender, .Property = name });
}

void DataModel::OnError(const LogNotification& cmd) { Notify(cmd); }

void DataModel::Execute(const SelectEntryCommand& cmd) {
    _queue->Enqueue([=]() {

        if (!CanCompile()) {
            return;
        }

        auto entry = _dir->FindEntry(cmd.Path);

        _activeEntry = entry;

        if (!entry) return;

        Notify(IDataModelObserver::EntrySelectedNotification{
            .SelectedEntry = entry->CreateView(_queue) });
        });
}

void DataModel::Execute(const RenameEntryCommand& cmd) {
    _queue->Enqueue([=]() {
        auto oldEntry = _dir->FindEntry(cmd.OldPath);
        if (!oldEntry) {
            Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.OldPath.Path));
            return;
        }

        auto newEntry = _dir->FindEntry(cmd.NewPath);
        if (newEntry) {
            Notify(LogError(LOG_ENTRY_ALREADY_EXISTS, cmd.NewPath.Path));
            return;
        }

        oldEntry = _dir->Remove(cmd.OldPath);
        assert(oldEntry);
        _dir->Add(cmd.NewPath, oldEntry);
        });
}

void DataModel::Execute(const CreateNodeCommand& cmd) {
    _queue->Enqueue([=]() {
        int suffix = 0;
        auto path = cmd.Path;

        while (auto node = _dir->FindEntry(path)) {
            path = { cmd.Path.Path + "." + std::to_string(suffix++) };
        }

        std::shared_ptr<Entry> entry;

        if (cmd.Type == "Group") {
            entry = std::make_shared<GroupEntry>();
        }
        else if (cmd.Type == "Transform") {
            entry = std::make_shared<TransformProxyEntry>(EntryPath{});
        }
        else if (cmd.Type == "Localized") {
            entry = std::make_shared<LocalizedEntry>();
        }

        if (entry) {
            _dir->Add(path, entry);
        }
        });
}

void DataModel::Execute(const SaveToFileCommand& cmd) {
    _queue->Enqueue([=]() {
        nlohmann::json j;

        auto& packages = j["packages"];

        for (auto& [name, info] : _packagePreviewRoots) {
            nlohmann::json o;
            o["name"] = name;
            o["path"] = info.Path;
            packages.push_back(o);
        }

        {
            auto& dir = j["catalog"];

            auto scene = _dir->FindEntry({ ROOT_SCENE });

            if (scene) {
                scene->Serialize(dir);
            }
        }

        {
            auto& dir = j["config"];

            auto config = _dir->FindEntry({ ROOT_CONFIG });

            if (config) {
                config->Serialize(dir);
            }
        }

        std::ofstream stream(cmd.Path, std::ios::binary);
        if (stream.is_open()) {
            auto str = j.dump(4);
            stream.write(str.data(), str.size());
        }
        });
}

// template <typename Output, typename... Next>
// class GeneratorBlock {
// public:
//     GeneratorBlock(std::function<Output()> fn) : _fn{ fn } {}


// private:
//     std::function<Output()> _fn;
//     std::tuple<Next...> _next;
// };

// template <typename Derived, typename Input, typename Output, typename... Next>
// class TransformBlock {
// public:

//     void operator () (Input i) {
//         auto o = Derived::Transform(i);
//         std::apply([&](auto&&... args) {
//             (args(o), ...);
//             }, this->_next);
//     }

// private:
//     std::tuple<Next...> _next;
// };

// template <typename Derived, typename Input>
// class FinalBlock {
// public:

//     void operator() (Input inp) {
//         Derived::operator() (inp);
//     }

// };

// template<typename... Next>
// class OpenBinaryStream : public TransformBlock<std::filesystem::path, std::shared_ptr<std::ifstream>, Next...> {
//     using Base = TransformBlock<std::filesystem::path, std::shared_ptr<std::ifstream>, Next...>;
// public:

//     std::shared_ptr<std::ifstream> Transform(std::filesystem::path path) {
//         return std::make_shared<std::ifstream>(path, std::ios::binary);
//     }

// };

// class ValidateStream : public FinalBlock<ValidateStream, std::shared_ptr<std::ifstream>> {
//     using Base = FinalBlock<ValidateStream, std::shared_ptr<std::ifstream>>;
// public:

//     void operator() (std::shared_ptr<std::ifstream> stream) {
//         // if (!stream.is_open()) {
//         //         Notify(LogNotification{.Code = EDITOR_ERROR_FILE_NOT_FOUND,
//         //                                .StrParamter = cmd.Path.string()});
//         //         return;
//         //     }
//         // }
//     }
// };

// template<typename... Next>
// class ReadAllTextFromStream : public TransformBlock<ReadAllTextFromStream<Next...>, std::shared_ptr<std::ifstream>, std::string, Next...> {
// public:

//     std::string Transform(std::shared_ptr<std::ifstream> stream) {
//         return std::string(std::istreambuf_iterator<char>(stream),
//             std::istreambuf_iterator<char>());
//     }
// };

// template<typename... Next>
// class StringToJsonTransform : public TransformBlock<StringToJsonTransform<Next...>, std::shared_ptr<std::ifstream>, std::string, Next...> {
//     public:

//         nlohmann::json Transform(std::string stream) {
//         return std::string(std::istreambuf_iterator<char>(stream),
//             std::istreambuf_iterator<char>());
//     }
// };

void DataModel::Execute(const ImportFromFileCommand& cmd) {
    DenyCompilation();

    _queue->Enqueue([=]() {

        {
            // Ensure required folders exists
            auto parent = std::filesystem::path(cmd.Path).parent_path();
            auto rawFolder = parent / "Raw";
            if (!std::filesystem::exists(rawFolder)) {
                std::filesystem::create_directory(rawFolder);
            }
        }

        std::ifstream stream(cmd.Path, std::ios::binary);
        if (!stream.is_open()) {
            Notify(LogNotification{ .Code = EDITOR_ERROR_FILE_NOT_FOUND,
                                   .StrParamter = cmd.Path.string() });
            return;
        }

        std::string text((std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>());

        try {
            auto o = nlohmann::json::parse(text);
            if (auto it = o.find("packages"); it != o.end()) {
                for (auto entry : *it) {
                    auto name = ::Deserialize(entry, "name", std::string{});
                    auto path = ::Deserialize(entry, "path", std::string{});
                    if (name.empty() || path.empty()) {
                        Notify(LogWarning(LOG_EMPTY_PACKAGE_REFERENCE));
                        continue;
                    }
                    Execute(IDataModelEditor::ImportFileCommand{
                        .FilePath = path,
                        .Options = _options,
                        .ProjectPath = cmd.Path.parent_path()
                        });
                }
            }
            else {
                throw std::runtime_error("'packages' section not found.");
            }

            {
                auto scene = std::make_shared<GroupEntry>();

                if (auto it = o.find("catalog"); it != o.end()) {
                    scene->Deserialize(*it);
                    _dir->Add({ ROOT_SCENE }, scene);
                }
                else {
                    throw std::runtime_error("'catalog' section not found.");
                }
            }

            {
                auto config = _dir->FindEntry({ ROOT_CONFIG });
                assert(config);

                if (auto it = o.find("config"); it != o.end()) {
                    config->Deserialize(*it);
                }
            }
        }
        catch (const std::exception& e) {
            Notify(
                LogNotification{ .Code = EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID,
                                .StrParamter = e.what() + text });
        }
        });

    AllowCompilation();
}

void DataModel::Execute(const MoveEntryCommand& cmd) {
    _queue->Enqueue([=]() {
        auto o = _dir->Remove(cmd.SourcePath);
        if (!o) {
            std::cerr << "Can't move entry " << cmd.SourcePath.Path << " to "
                << cmd.TargetPath.Path << " because source is not found.";
            return;
        }

        _dir->Add(cmd.TargetPath.Append(cmd.SourcePath.GetLeafName()), o);
        });
}

void DataModel::Execute(const CopyEntryCommand& cmd) {
    _queue->Enqueue([=]() {
        auto o = _dir->FindEntry(cmd.SourcePath);
        if (!o) {
            std::cerr << "Can't clone entry " << cmd.SourcePath.Path << " to "
                << cmd.TargetPath.Path << " because source is not found.";
            return;
        }

        auto obj = o->Clone();

        _dir->Add(cmd.TargetPath.Append(cmd.SourcePath.GetLeafName()), obj);
        });
}

void DataModel::Execute(const RemoveEntryCommand& cmd) {
    _queue->Enqueue([=]() { _dir->Remove(cmd.Path); });
}

void DataModel::OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) {
    Notify(IDataModelObserver::ItemAddedNotification{ .Path = path,
                                                     .Type = entry->GetType() });
}

void DataModel::OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) {
    Notify(IDataModelObserver::ItemRemovedNotification{
        .Path = path, .Type = entry->GetType() });
}

void DataModel::Execute(const CopyNodeCommand& cmd) {
    _queue->Enqueue([=]() {
        auto entry = _dir->FindEntry(cmd.SourcePath);

        if (!entry) {
            std::cerr << "Can't copy " << cmd.SourcePath.Path << " to "
                << cmd.TargetPath.Path << ". Entry not found."
                << std::endl;
            return;
        }

        auto localPath =
            cmd.TargetPath.Path + "/" + cmd.SourcePath.GetLeafName();
        _dir->Add({ localPath }, entry->CreateProxy(cmd.SourcePath));
        });
}

struct CompilationState {
    bool ShowTransforms;
    vsg::ref_ptr<vsg::Node> TransformProxy;
    vsg::ref_ptr<vsg::Node> ActiveCursor;
    std::shared_ptr<Entry> ActiveEntry;
};

vsg::ref_ptr<vsg::Node> Compile(const CompilationState& state,
    std::shared_ptr<Entry> entry) {
    if (!entry) return {};

    if (auto g = std::dynamic_pointer_cast<GeometryEntry>(entry))
        return g->GetGeometry();

    auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry);

    if (!dir) {
        std::cerr << "Unexpected entry type "
            << magic_enum::enum_name(entry->GetType()) << std::endl;
        return {};
    }

    vsg::ref_ptr<vsg::Group> group;

    if (auto g = std::dynamic_pointer_cast<GroupEntry>(entry)) {
        group = g->GetGroup();
    }

    if (auto g = std::dynamic_pointer_cast<MaterialEntry>(entry)) {
        group = g->GetState();
    }

    if (auto g = std::dynamic_pointer_cast<TransformEntry>(entry)) {
        group = g->GetTransform();

        if (state.ShowTransforms && state.TransformProxy) {
            group->addChild(state.TransformProxy);
        }
    }

    if (!group) {
        std::cerr << "Unexpected directory type "
            << magic_enum::enum_name(entry->GetType()) << std::endl;
        return {};
    }

    if (state.ActiveEntry == entry && state.ActiveCursor) {
        group->addChild(state.ActiveCursor);
    }

    dir->ForEachEntry([&](auto name, auto entry) {
        auto child = Compile(state, entry);
        if (child) {
            group->addChild(child);
        }
        });

    return group;
}

void DataModel::CreateAxis() {
    _builder->options = _options;
    stateInfo.lighting = false;

    vsg::GeometryInfo geomInfo;
    geomInfo.dx.set(4.0f, 0.0f, 0.0f);
    geomInfo.dy.set(0.0f, 0.01f, 0.0f);
    geomInfo.dz.set(0.0f, 0.0f, 0.01f);
    geomInfo.color.set(1, 0, 0, 1);
    geomInfo.position.set(2, 0, 0);

    auto x = _builder->createBox(geomInfo, stateInfo);

    geomInfo.dx.set(0.01f, 0.0f, 0.0f);
    geomInfo.dy.set(0.0f, 4.0f, 0.0f);
    geomInfo.dz.set(0.0f, 0.0f, 0.01f);
    geomInfo.color.set(0, 1, 0, 1);
    geomInfo.position.set(0, 2, 0);

    auto y = _builder->createBox(geomInfo, stateInfo);

    geomInfo.dx.set(0.01f, 0.0f, 0.0f);
    geomInfo.dy.set(0.0f, 0.01f, 0.0f);
    geomInfo.dz.set(0.0f, 0.0f, 4.0f);
    geomInfo.color.set(0, 0, 1, 1);
    geomInfo.position.set(0, 0, 2);

    auto z = _builder->createBox(geomInfo, stateInfo);

    _axis = vsg::Group::create();
    _axis->addChild(x);
    _axis->addChild(y);
    _axis->addChild(z);

    stateInfo.lighting = true;
}

void DataModel::Execute(const CompileSceneCommand& cmd) {

    _queue->Enqueue([=]() {

        if (!CanCompile()) {
            Notify(IDataModelObserver::SceneCompeledNotification{ .Root = {} });
            return;
        }

        auto config = GetConfig();
        assert(config);

        auto scale = vsg::MatrixTransform::create();
        scale->matrix = vsg::scale(0.01f, 0.01f, 0.01f);
        scale->addChild(_axis);

        CompilationState state{ .ShowTransforms = config->GetShowTransform(),
                               .TransformProxy = scale,
                               .ActiveCursor = scale,
                               .ActiveEntry = _activeEntry };

        if (cmd.Root.GetName() == ROOT_SCENE) {
            auto root = Compile(state, _dir->FindEntry({ cmd.Root.GetName() }));
            Notify(IDataModelObserver::SceneCompeledNotification{ .Root = root });
        }
        else if (cmd.Root.GetName() == ROOT_PACKAGES) {
            auto it = _packagePreviewRoots.find(cmd.Root.GetNext().GetName());
            if (it == _packagePreviewRoots.end()) {
                std::cerr << "Package " << cmd.Root.GetNext().GetName()
                    << " preview not found" << std::endl;
                return;
            }
            Notify(IDataModelObserver::SceneCompeledNotification{
                .Root = it->second.Root });
        }
        });
}

std::shared_ptr<ConfigEntry> DataModel::GetConfig() {
    return std::static_pointer_cast<ConfigEntry>(
        _dir->FindEntry({ ROOT_CONFIG }));
}

void DataModel::DenyCompilation() {
    _queue->Enqueue([=]() { _denyCompilation++; });
}

void DataModel::AllowCompilation() {
    _queue->Enqueue([=]() { _denyCompilation--; });
}

void DataModel::Execute(const ExportToFileCommand& cmd) {
    _queue->Enqueue([=]() {
        if (!CanCompile()) {
            Notify(LogError(LOG_ENTRY_BUSY));
            return;
        }

        CompilationState state{ .ShowTransforms = false,
                               .TransformProxy = {},
                               .ActiveCursor = {},
                               .ActiveEntry = nullptr };

        const auto root = Compile(state, _dir->FindEntry({ ROOT_SCENE }));

        if (!root) {
            Notify(LogError(LOG_ENTRY_COMPILATION_FAILED, ROOT_SCENE));
            return;
        }

        vsg::write(root, cmd.Path);
        });
}

void DataModel::Execute(const AddLanguageCommand& cmd) {
    _queue->Enqueue([=]() {
        auto cfg = GetConfig();
        if (!cfg->AddLanguage(cmd.Value)) {
            Notify(LogError(LOG_ENTRY_ALREADY_EXISTS, cmd.Value));
            return;
        }

        Notify(
            IDataModelObserver::LanguageAddedNotification{ .Value = cmd.Value });
        });
}

void DataModel::Execute(const RemoveLanguageCommand& cmd) {
    _queue->Enqueue([=]() {
        auto cfg = GetConfig();
        if (!cfg->RemoveLanguage(cmd.Value)) {
            Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.Value));
            return;
        }

        Notify(
            IDataModelObserver::LanguageRemoveNotification{ .Value = cmd.Value });
        });
}

void DataModel::Execute(const RenameLanguageCommand& cmd) {
    _queue->Enqueue([=]() {
        auto cfg = GetConfig();
        auto langs = cfg->GetLanguages();
        if (auto it = std::find(langs.begin(), langs.end(), cmd.OldValue);
            it == langs.end()) {
            Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.OldValue));
            return;
        }

        if (auto it = std::find(langs.begin(), langs.end(), cmd.NewValue);
            it != langs.end()) {
            Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.NewValue));
            return;
        }

        cfg->RemoveLanguage(cmd.OldValue);
        cfg->AddLanguage(cmd.NewValue);

        Notify(IDataModelObserver::LanguageRemoveNotification{
            .Value = cmd.OldValue });
        Notify(IDataModelObserver::LanguageAddedNotification{ .Value =
                                                                 cmd.NewValue });
        });
}

void DataModel::Execute(const RequestSuggestedChildrenCommand& cmd) {
    _queue->Enqueue([=]() {
        auto entry = _dir->FindEntry(cmd.Path);
        if (!entry) {
            Notify(LogError(LOG_ENTRY_NOT_FOUND, cmd.Path.Path));
            return;
        }

        IDataModelObserver::SuggestedChildrenNotification r;
        r.Context = cmd.Context;
        r.Path = cmd.Path;

        switch (entry->GetType()) {
        case EntryType::Transform:
        case EntryType::Material:
        case EntryType::Group:
            r.Suggestions.emplace_back("Group", "Group");
            // r.Suggestions.emplace_back(magic_enum::enum_name(EntryType::Material),
            // magic_enum::enum_name(EntryType::Material));
            r.Suggestions.emplace_back("Transform", "Transform");
            r.Suggestions.emplace_back("Localized", "Localized");
            break;

        case EntryType::Geometry:
        case EntryType::Config:
            break;

        case EntryType::Localized: {
            auto config = GetConfig();
            for (auto l : config->GetLanguages()) {
                if (!_dir->FindEntry(cmd.Path.Append(l))) {
                    r.Suggestions.emplace_back("Group", l);
                }
            }
        } break;
        }

        Notify(r);
        });
}

void DataModel::OnSubscribed(std::shared_ptr<IDataModelObserver> observer) {
    observer->Execute(IDataModelObserver::ConfigNotification{
                    .Config = std::static_pointer_cast<ConfigEntry>(
                        GetConfig()->CreateView(this->_queue)) });
}
