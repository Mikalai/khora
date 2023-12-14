#include <iostream>
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

            {
                std::unique_lock lock{ _packagePreviewRoots_cs };
                _packagePreviewRoots[packageName] = root;
            }

            WorldCompiler compiler;
            root->accept(compiler);

            for (auto& o : compiler.objects) {
                std::string path = o.first;

                if (auto tr = std::get<0>(o.second).cast<vsg::MatrixTransform>(); tr) {
                    _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_TRANSFORMS + "/" + o.first }, std::make_shared<TransformEntry>(tr), *this);

                    for (auto child : tr->children) {
                        if (auto m = child.cast<vsg::StateGroup>(); m) {
                            _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_MATERIALS + "/" + o.first }, std::make_shared<MaterialEntry>(m), *this);
                        }
                    }
                }
                if (auto tr = std::get<0>(o.second).cast<vsg::VertexIndexDraw>(); tr) {
                    _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_GEOMETRIES + "/" + path }, std::make_shared<GeometryEntry>(tr), *this);
                }
                if (auto tr = std::get<0>(o.second).cast<vsg::StateGroup>(); tr) {
                    _dir->Add({ ROOT_PACKAGES + "/" + packageName + "/" + PACKAGE_ENTRY_MATERIALS + "/" + path }, std::make_shared<MaterialEntry>(tr), *this);
                }
            }
        }
        });
}

void DataModel::Subscribe(IDataModelObserver* observer)
{
    _observers.push_back(observer);
}

void DataModel::Execute(const MoveEntryCommand& cmd)
{
    auto o = _dir->Remove(cmd.SourcePath, *this);
    if (!o) {
        std::cerr << "Can't move entry " << cmd.SourcePath.Path << " to " << cmd.TargetPath.Path << " because source is not found.";
        return;
    }

    _dir->Add(cmd.TargetPath.Append(cmd.SourcePath.GetLeafName()), o, *this);
}

void DataModel::Execute(const RemoveEntryCommand& cmd)
{
    /*std::unique_lock lock{ _dir_cs };

    _dir->RemoveObject(cmd.Path);
    Notify(IDataModelObserver::ItemRemovedNotification{ .Path = cmd.Path });*/
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
    boost::asio::post(_ctx, [this, cmd]() {

        auto entry = _dir->FindEntry(cmd.SourcePath);

        if (!entry) {
            std::cerr << "Can't copy " << cmd.SourcePath.Path << " to " << cmd.TargetPath.Path << ". Entry not found." << std::endl;
            return;
        }

        auto copy = entry->Clone();

        auto localPath = cmd.TargetPath.Path + "/" + cmd.SourcePath.GetLeafName();
        _dir->Add({ localPath }, copy, *this);
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
    if (cmd.Root.GetName() == ROOT_SCENE) {
        auto root = Compile(_dir->FindEntry({ cmd.Root.GetName() }));
        Notify(IDataModelObserver::SceneCompeledNotification{ .Root = root });
    }
    else if (cmd.Root.GetName() == ROOT_PACKAGES) {
        std::unique_lock lock{ _packagePreviewRoots_cs };
        auto it = _packagePreviewRoots.find(cmd.Root.GetNext().GetName());
        if (it == _packagePreviewRoots.end()) {
            std::cerr << "Package " << cmd.Root.GetNext().GetName() << " preview not found" << std::endl;
            return;
        }
        Notify(IDataModelObserver::SceneCompeledNotification{ .Root = it->second });
    }
}

IDataModelEditor::~IDataModelEditor() {

}

IDataModelObserver::~IDataModelObserver() {

}
