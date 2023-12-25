#pragma once

#include <vsg/all.h>
#include "Errors.h"
#include "EntryType.h"
#include "EntryPath.h"

class Entry;
class ConfigEntry;

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

    struct ModelResetNotification {

    };

    virtual void Execute(const ModelResetNotification& cmd) = 0;

    virtual void Execute(const LogNotification& cmd) = 0;

    struct EntrySelectedNotification {
        std::shared_ptr<Entry> SelectedEntry;
    };

    virtual void Execute(const EntrySelectedNotification& cmd) = 0;

    struct EntryPropertyChangedNotification {
        std::shared_ptr<Entry> ChangedEntry;
        std::string_view Property;
    };

    virtual void Execute(const EntryPropertyChangedNotification& cmd) = 0;

    struct ConfigNotification {
        std::shared_ptr<ConfigEntry> Config;
    };

    virtual void Execute(const ConfigNotification& cmd) = 0;

    struct LanguageAddedNotification {
        std::string Value;
    };

    virtual void Execute(const LanguageAddedNotification& cmd) = 0;

    struct LanguageRemoveNotification {
        std::string Value;
    };

    virtual void Execute(const LanguageRemoveNotification& cmd) = 0;

    struct SuggestedChildrenNotification {
        struct Suggestion {
            std::string Type;
            std::string Name;
        };
        std::string Context;
        EntryPath Path;
        std::vector<Suggestion> Suggestions;
    };

    virtual void Execute(const SuggestedChildrenNotification& cmd) = 0;

    struct BulkOperationStartedNotification {

    };

    virtual void Execute(const BulkOperationStartedNotification& cmd) = 0;

    struct BulkOperationEndedNotification {

    };

    virtual void Execute(const BulkOperationEndedNotification& cmd) = 0;

};



class DataModelObserverAdapter : public IDataModelObserver {
public:
    DataModelObserverAdapter(IDataModelObserver& other)
        : _other{ other }
    {

    }

    void Execute(const CompileCommand& cmd) override { this->_other.Execute(cmd); }
    void Execute(const ItemAddedNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const ItemRemovedNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const SceneCompeledNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const ModelResetNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const LogNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const EntrySelectedNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const EntryPropertyChangedNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const ConfigNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const LanguageAddedNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const LanguageRemoveNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const SuggestedChildrenNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const BulkOperationStartedNotification& cmd) override { this->_other.Execute(cmd); }
    void Execute(const BulkOperationEndedNotification& cmd) override { this->_other.Execute(cmd); }

private:
    IDataModelObserver& _other;
};
