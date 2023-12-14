#pragma once

#include <queue>
#include <vsg/all.h>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind/bind.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

#include "IDataModelEditor.h"
#include "IDirectoryObserver.h"
#include "IDataModelObserver.h"
#include "DirectoryEntry.h"
#include "GroupEntry.h"
#include "AsyncQueue.h"

const std::string ROOT_PACKAGES{ "PACKAGES" };
const std::string ROOT_SCENE{ "SCENE" };
const std::string PACKAGE_ENTRY_TRANSFORMS{ "Transforms" };
const std::string PACKAGE_ENTRY_GEOMETRIES{ "Geometries" };
const std::string PACKAGE_ENTRY_MATERIALS{ "Materials" };

class DataModel : 
    public IDataModelEditor, 
    public IDirectoryObserver, 
    public std::enable_shared_from_this<DataModel> {
public:
    
    DataModel(boost::asio::io_context& ctx);
    virtual ~DataModel();

    void Execute(const ImportFileCommand& cmd) override;
    void Execute(const CompileSceneCommand& cmd) override;
    void Execute(const CopyNodeCommand& cmd) override;
    void Execute(const MoveEntryCommand& cmd) override;
    void Execute(const RemoveEntryCommand& cmd) override;
    void Execute(const ExportToFileCommand& cmd) override;
    void Execute(const ImportFromFileCommand& cmd) override;

    void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) override;
    void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) override;

    void Subscribe(IDataModelObserver* observer) override;

    template<typename T>
    void Notify(T&& value) {
        std::for_each(this->_observers.begin(), this->_observers.end(), [&](auto o) {
            o->Execute(value);
        });
    }

private:

    struct PackageInfo {
        std::filesystem::path Path;
        vsg::ref_ptr<vsg::Node> Root;
    };

    std::unordered_map<std::string, PackageInfo> _packagePreviewRoots;
    std::shared_ptr<AsyncQueue> _queue;

    std::shared_ptr<DirectoryEntry> _dir = std::make_shared<GroupEntry>();
    std::vector<IDataModelObserver*> _observers;
    boost::asio::io_context& _ctx;    
};
