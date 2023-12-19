#pragma once

#include <semaphore>
#include <vsg/all.h>
#include "DirectoryEntry.h"

class AsyncQueue;

class ConfigEntry : public DirectoryEntry {
public:
    
    EntryType GetType() const override;

    virtual bool GetShowTransform() const;
    virtual void SetShowTransform(bool value);

    virtual std::shared_ptr<Entry> CreateView(std::shared_ptr<AsyncQueue> sync) override;

    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path, const EntryProperties& properties) override;
    
    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;

protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

private:
    bool _showTransform{ true };
};

class ConfigEntryView : public ConfigEntry {
public:

    ConfigEntryView(std::shared_ptr<ConfigEntry> dataModel, std::shared_ptr<AsyncQueue> syncContext)
        : _model{ dataModel }
        , _sync{ syncContext } {}

    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;

    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path, const EntryProperties& properties) override;

    virtual bool GetShowTransform() const override;
    virtual void SetShowTransform(bool value) override;

protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

private:
    std::shared_ptr<ConfigEntry> _model;
    std::shared_ptr<AsyncQueue> _sync;
};
