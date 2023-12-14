#include <iostream>
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>
#include <boost/asio/post.hpp>
#include <boost/algorithm/string.hpp>
#include <filesystem>
#include "DataModel.h"
#include "../Render/WorldCompiler.h"

#include "GeometryEntry.h"
#include "GroupEntry.h"
#include "TransformEntry.h"
#include "MaterialEntry.h"


DataModel::DataModel(boost::asio::io_context& ctx)
    : _ctx{ ctx } {
    (_queue = std::make_shared<AsyncQueue>(ctx))->Start();
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
                        _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_TRANSFORMS + "/" + o.first }, std::make_shared<TransformPackageEntry>(tr), *this);

                        for (auto child : tr->children) {
                            if (auto m = child.cast<vsg::StateGroup>(); m) {
                                _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_MATERIALS + "/" + o.first }, std::make_shared<MaterialPackageEntry>(m), *this);
                            }
                        }
                    }
                    if (auto tr = std::get<0>(o.second).cast<vsg::VertexIndexDraw>(); tr) {
                        _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_GEOMETRIES + "/" + path }, std::make_shared<GeometryPackageEntry>(tr), *this);
                    }
                    if (auto tr = std::get<0>(o.second).cast<vsg::StateGroup>(); tr) {
                        _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_MATERIALS + "/" + path }, std::make_shared<MaterialPackageEntry>(tr), *this);
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
        });
}

void DataModel::Execute(const MoveEntryCommand& cmd)
{
    _queue->Enqueue([=]() {
        auto o = _dir->Remove(cmd.SourcePath, *this);
        if (!o) {
            std::cerr << "Can't move entry " << cmd.SourcePath.Path << " to " << cmd.TargetPath.Path << " because source is not found.";
            return;
        }

        _dir->Add(cmd.TargetPath.Append(cmd.SourcePath.GetLeafName()), o, *this);
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
        _dir->Add({ localPath }, entry->CreateProxy(_dir, cmd.SourcePath), *this);
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
