#pragma once

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

    struct RemoveEntryCommand {
        EntryPath Path;
    };

    virtual void Execute(const RemoveEntryCommand& cmd) = 0;

    virtual void Subscribe(IDataModelObserver* observer) = 0;
};
