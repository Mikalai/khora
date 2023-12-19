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
#include "IEntryObserver.h"
#include "IDataModelObserver.h"
#include "DirectoryEntry.h"
#include "GroupEntry.h"
#include "AsyncQueue.h"

const std::string ROOT_PACKAGES{ "PACKAGES" };
const std::string ROOT_SCENE{ "SCENE" };
const std::string ROOT_CONFIG{ "CONFIG" };

const std::string PACKAGE_ENTRY_TRANSFORMS{ "Transforms" };
const std::string PACKAGE_ENTRY_GEOMETRIES{ "Geometries" };
const std::string PACKAGE_ENTRY_MATERIALS{ "Materials" };

class DataModel : 
    public IDataModelEditor, 
    public IEntryObserver, 
    public std::enable_shared_from_this<DataModel> {
protected:    
    DataModel(boost::asio::io_context& ctx);

public:

    static std::shared_ptr<DataModel> Create(boost::asio::io_context& ctx);

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
    void CreateAxis();
    vsg::StateInfo stateInfo;
    vsg::ref_ptr<vsg::Builder> _builder = vsg::Builder::create();
    vsg::ref_ptr<vsg::Group> _axis;
    std::shared_ptr<Entry> _activeEntry;
    std::shared_ptr<ConfigEntry> GetConfig();

    void DenyCompilation();
    void AllowCompilation();
    bool CanCompile() const { return _denyCompilation == 0; }

    struct PackageInfo {
        std::filesystem::path Path;
        vsg::ref_ptr<vsg::Node> Root;
    };

    std::int32_t _denyCompilation{ 0 };
    vsg::ref_ptr<vsg::Options> _options = vsg::Options::create();
    std::unordered_map<std::string, PackageInfo> _packagePreviewRoots;
    std::shared_ptr<AsyncQueue> _queue;

    std::shared_ptr<DirectoryEntry> _dir = std::make_shared<GroupEntry>();
    std::vector<IDataModelObserver*> _observers;
    boost::asio::io_context& _ctx;    

    // Inherited via IDataModelEditor
    void Execute(const ResetModelCommand& cmd) override;

    // Inherited via IEntryObserver
    void OnPropertyChanged(std::shared_ptr<Entry> sender, std::string_view name) override;

    // Inherited via IDataModelEditor
    void Execute(const SelectEntryCommand& cmd) override;

    // Inherited via IDataModelEditor
    std::shared_ptr<AsyncQueue> GetSyncContext() override;

    // Inherited via IDataModelEditor
    void Execute(const RenameEntryCommand& cmd) override;

    // Inherited via IDataModelEditor
    void Execute(const CreateNodeCommand& cmd) override;

    // Inherited via IDataModelEditor
    void Execute(const CopyEntryCommand& cmd) override;
};
