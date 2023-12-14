#pragma once

#include <vsg/all.h>
#include "DirectoryEntry.h"

class MaterialEntry : public DirectoryEntry {
public:
    EntryType GetType() const override;
    virtual vsg::ref_ptr<vsg::StateGroup> GetState() const = 0;
};

class MaterialPackageEntry : public MaterialEntry {
public:

    MaterialPackageEntry(vsg::ref_ptr<vsg::StateGroup> state)
        : _state{ state } {
    }

    vsg::ref_ptr<vsg::StateGroup> GetState() const override;
    std::shared_ptr<Entry> Clone() override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

private:
    vsg::ref_ptr<vsg::StateGroup> _state;
};

class MaterialProxyEntry : public MaterialEntry {
public:
    MaterialProxyEntry(EntryPath path);

    vsg::ref_ptr<vsg::StateGroup> GetState() const override;
    std::shared_ptr<Entry> Clone() override;
    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;
    
    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path, const EntryProperties& properties) override;

private:
    EntryPath _path;
};
