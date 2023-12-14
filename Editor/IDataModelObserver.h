#pragma once

class IDataModelObserver {
public:
    virtual ~IDataModelObserver();

    struct CompileCommand {
        vsg::ref_ptr<vsg::Node> Object;
        std::function<void(vsg::ref_ptr<vsg::Node>, vsg::CompileResult&)> OnComplete;
    };

    virtual void Execute(const CompileCommand& cmd) = 0;

    struct ItemAddedNotification {
        EntryPath Path;
        EntryType Type;
    };

    virtual void Execute(const ItemAddedNotification& cmd) = 0;

    struct ItemRemovedNotification {
        EntryPath Path;
        EntryType Type;
    };

    virtual void Execute(const ItemRemovedNotification& cmd) = 0;

    struct SceneCompeledNotification {
        vsg::ref_ptr<vsg::Node> Root;
    };

    virtual void Execute(const SceneCompeledNotification& cmd) = 0;    
};

