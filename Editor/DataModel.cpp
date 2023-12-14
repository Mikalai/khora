#include <iostream>
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>
#include <boost/asio/post.hpp>
#include <boost/algorithm/string.hpp>
#include <filesystem>
#include "DataModel.h"
#include "../Render/WorldCompiler.h"

#include "Serializer.h"
#include "GeometryEntry.h"
#include "GroupEntry.h"
#include "TransformEntry.h"
#include "MaterialEntry.h"


DataModel::DataModel(boost::asio::io_context& ctx)
    : _ctx{ ctx } {
    (_queue = std::make_shared<AsyncQueue>(ctx))->Start();
}

std::shared_ptr<DataModel> DataModel::Create(boost::asio::io_context& ctx) {
    std::shared_ptr<DataModel> r{ new DataModel{ ctx } };
    r->Execute(IDataModelEditor::ResetModelCommand{});
    return r;
}

DataModel::~DataModel() {

}

void DataModel::Execute(const ImportFileCommand& cmd)
{
    boost::asio::post(_ctx, [this, cmd]() {

        if (auto root = vsg::read_cast<vsg::Node>(cmd.FilePath, cmd.Options); root) {

            Notify(IDataModelObserver::CompileCommand{ .Object = root, .OnComplete = [&](auto object, auto result) {
                }
                });

            auto packageName = std::filesystem::path(cmd.FilePath).filename().string();


            _queue->Enqueue([=]() {

                _packagePreviewRoots[packageName] = PackageInfo{ .Path = cmd.FilePath, .Root = root };

                WorldCompiler compiler;
                root->accept(compiler);

                for (auto& o : compiler.objects) {
                    std::string path = o.first;

                    if (auto tr = std::get<0>(o.second).cast<vsg::MatrixTransform>(); tr) {
                        _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_TRANSFORMS + "/" + o.first }, std::make_shared<TransformPackageEntry>(tr));

                        for (auto child : tr->children) {
                            if (auto m = child.cast<vsg::StateGroup>(); m) {
                                _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_MATERIALS + "/" + o.first }, std::make_shared<MaterialPackageEntry>(m));
                            }
                        }
                    }
                    if (auto tr = std::get<0>(o.second).cast<vsg::VertexIndexDraw>(); tr) {
                        _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_GEOMETRIES + "/" + path }, std::make_shared<GeometryPackageEntry>(tr));
                    }
                    if (auto tr = std::get<0>(o.second).cast<vsg::StateGroup>(); tr) {
                        _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_MATERIALS + "/" + path }, std::make_shared<MaterialPackageEntry>(tr));
                    }
                }
                });
        }
        });
}

void DataModel::Subscribe(IDataModelObserver* observer)
{
    _queue->Enqueue([=]() {
        _observers.push_back(observer);
    });
}

void DataModel::Execute(const ResetModelCommand& cmd)
{
    _queue->Enqueue([=]() {
        _dir = std::make_shared<GroupEntry>();
        _dir->AddObserver(shared_from_this());
        _packagePreviewRoots.clear();
        Notify(IDataModelObserver::ModelResetNotification{});
    });
}

void DataModel::OnPropertyChanged(std::shared_ptr<Entry> sender, std::string_view name)
{
}

void DataModel::Execute(const ExportToFileCommand& cmd) {
    _queue->Enqueue([=]() {
        nlohmann::json j;

        auto& packages = j["packages"];

        for (auto& [name, info] : _packagePreviewRoots) {
            nlohmann::json o;
            o["name"] = name;
            o["path"] = info.Path;
            packages.push_back(o);
        }

        auto& dir = j["catalog"];

        auto scene = _dir->FindEntry({ ROOT_SCENE });
        
        if (scene) {
            scene->Serialize(dir);
        }

        std::ofstream stream(cmd.Path, std::ios::binary);
        if (stream.is_open()) {
            auto str = j.dump(4);
            stream.write(str.data(), str.size());
        }
    });
}

void DataModel::Execute(const ImportFromFileCommand& cmd) {
    _queue->Enqueue([=]() {
        std::ifstream stream(cmd.Path, std::ios::binary);
        if (!stream.is_open()) {
            Notify(LogNotification{ .Code = EDITOR_ERROR_FILE_NOT_FOUND, .StrParamter = cmd.Path.string() });
            return;
        }

        std::string text((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

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
                    Execute(IDataModelEditor::ImportFileCommand{ .FilePath = path, .Options = _options });
                }
            }
            else {
                throw std::runtime_error("'packages' section not found.");
            }

            auto scene = std::make_shared<GroupEntry>();

            if (auto it = o.find("catalog"); it != o.end()) {
                scene->Deserialize(*it);
                _dir->Add({ ROOT_SCENE }, scene);
            }
            else {
                throw std::runtime_error("'catalog' section not found.");
            }
        }
        catch (const std::exception& e) {
            Notify(LogNotification{ .Code = EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID, .StrParamter = e.what() + text});
        }
    });
}

void DataModel::Execute(const MoveEntryCommand& cmd)
{
    _queue->Enqueue([=]() {
        auto o = _dir->Remove(cmd.SourcePath);
        if (!o) {
            std::cerr << "Can't move entry " << cmd.SourcePath.Path << " to " << cmd.TargetPath.Path << " because source is not found.";
            return;
        }

        _dir->Add(cmd.TargetPath.Append(cmd.SourcePath.GetLeafName()), o);
    });
}

void DataModel::Execute(const RemoveEntryCommand& cmd)
{
    _queue->Enqueue([=]() {
        /*std::unique_lock lock{ _dir_cs };

        _dir->RemoveObject(cmd.Path);
        Notify(IDataModelObserver::ItemRemovedNotification{ .Path = cmd.Path });*/
    });
}

void DataModel::OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry)
{
    Notify(IDataModelObserver::ItemAddedNotification{ .Path = path, .Type = entry->GetType() });
}

void DataModel::OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry)
{
    Notify(IDataModelObserver::ItemRemovedNotification{ .Path = path, .Type = entry->GetType() });
}

void DataModel::Execute(const CopyNodeCommand& cmd)
{
    _queue->Enqueue([=]() {

        auto entry = _dir->FindEntry(cmd.SourcePath);

        if (!entry) {
            std::cerr << "Can't copy " << cmd.SourcePath.Path << " to " << cmd.TargetPath.Path << ". Entry not found." << std::endl;
            return;
        }

        auto localPath = cmd.TargetPath.Path + "/" + cmd.SourcePath.GetLeafName();
        _dir->Add({ localPath }, entry->CreateProxy(cmd.SourcePath));
    });
}

vsg::ref_ptr<vsg::Node> Compile(std::shared_ptr<Entry> entry) {
    if (!entry)
        return{};

    if (auto g = std::dynamic_pointer_cast<GeometryEntry>(entry))
        return g->GetGeometry();

    auto dir = std::dynamic_pointer_cast<DirectoryEntry>(entry);

    if (!dir) {
        std::cerr << "Unexpected entry type " << magic_enum::enum_name(entry->GetType()) << std::endl;
        return{};
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
    }

    if (!group) {
        std::cerr << "Unexpected directory type " << magic_enum::enum_name(entry->GetType()) << std::endl;
        return{};
    }

    dir->ForEachEntry([&](auto name, auto entry) {
        auto child = Compile(entry);
        if (child) {
            group->addChild(child);
        }
        });

    return group;
}

void DataModel::Execute(const CompileSceneCommand& cmd) {
    _queue->Enqueue([=]() {
        if (cmd.Root.GetName() == ROOT_SCENE) {
            auto root = Compile(_dir->FindEntry({ cmd.Root.GetName() }));
            Notify(IDataModelObserver::SceneCompeledNotification{ .Root = root });
        }
        else if (cmd.Root.GetName() == ROOT_PACKAGES) {
            auto it = _packagePreviewRoots.find(cmd.Root.GetNext().GetName());
            if (it == _packagePreviewRoots.end()) {
                std::cerr << "Package " << cmd.Root.GetNext().GetName() << " preview not found" << std::endl;
                return;
            }
            Notify(IDataModelObserver::SceneCompeledNotification{ .Root = it->second.Root });
        }
        });
}

IDataModelEditor::~IDataModelEditor() {

}

IDataModelObserver::~IDataModelObserver() {

}
