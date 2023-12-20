#pragma once

#include <filesystem>
#include "AsyncQueue.h"
#include <vsg/all.h>
#include "EntryPath.h"

class IDataModelObserver;

class IDataModelEditor {
public:
    virtual ~IDataModelEditor();

    struct ImportFileCommand {
        std::string FilePath;
        vsg::ref_ptr<vsg::Options> Options;
    };

    virtual void Execute(const ImportFileCommand& cmd) = 0;

    struct CompileSceneCommand {
        EntryPath Root;
    };

    virtual void Execute(const CompileSceneCommand& cmd) = 0;

    struct CopyNodeCommand {
        EntryPath SourcePath;
        EntryPath TargetPath;
    };

    virtual void Execute(const CopyNodeCommand& cmd) = 0;

    struct MoveEntryCommand {
        EntryPath SourcePath;
        EntryPath TargetPath;
    };

    virtual void Execute(const MoveEntryCommand& cmd) = 0;

    struct CopyEntryCommand {
        EntryPath SourcePath;
        EntryPath TargetPath;
    };

    virtual void Execute(const CopyEntryCommand& cmd) = 0;

    struct RemoveEntryCommand {
        EntryPath Path;
    };

    virtual void Execute(const RemoveEntryCommand& cmd) = 0;

    struct RenameEntryCommand {
        EntryPath OldPath;
        EntryPath NewPath;
    };

    virtual void Execute(const RenameEntryCommand& cmd) = 0;

    struct SaveToFileCommand {
        std::filesystem::path Path;
    };

    virtual void Execute(const SaveToFileCommand& cmd) = 0;

    struct ImportFromFileCommand {
        std::filesystem::path Path;
    };

    virtual void Execute(const ImportFromFileCommand& cmd) = 0;

    struct ResetModelCommand {
    };

    virtual void Execute(const ResetModelCommand& cmd) = 0;

    virtual void Subscribe(IDataModelObserver* observer) = 0;

    struct SelectEntryCommand {
        EntryPath Path;
    };

    virtual void Execute(const SelectEntryCommand& cmd) = 0;

    virtual std::shared_ptr<AsyncQueue> GetSyncContext() = 0;

    struct CreateNodeCommand {
        EntryPath Path;
        std::string Type;
    };

    virtual void Execute(const CreateNodeCommand& cmd) = 0;

    struct ExportToFileCommand {
        std::string Path;
    };

    virtual void Execute(const ExportToFileCommand& cmd) = 0;
};
