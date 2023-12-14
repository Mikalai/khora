#pragma once

#include <vsg/all.h>
#include "DirectoryEntry.h"

class TransformEntry : public DirectoryEntry {
public:
    
    virtual vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const = 0;
    EntryType GetType() const override;
};

class TransformPackageEntry final : public TransformEntry {
public:

    TransformPackageEntry(vsg::ref_ptr<vsg::MatrixTransform> transform)
        : _transform{ transform } {
    }

    bool CanAdd(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> Clone() override;
    vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const;
    std::shared_ptr<Entry> CreateProxy(std::shared_ptr<Entry> root, EntryPath path) override;

private:
    vsg::ref_ptr<vsg::MatrixTransform> _transform;

};

class TransformProxyEntry final : public TransformEntry {
public:

    TransformProxyEntry(EntryPath path, std::shared_ptr<Entry> root);

    std::shared_ptr<Entry> Clone() override;
    std::shared_ptr<Entry> CreateProxy(std::shared_ptr<Entry> root, EntryPath path) override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;
    vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const override;

    void SetOverride(bool flag) { _override = flag; }
    bool GetOverride() const { return _override; }

    void SetPosition(vsg::dvec3 value) { _position = value; }
    vsg::dvec3 GetPosition() const { return _position; }

    void SetScale(vsg::dvec3 value) { _scale = value; }

    void Serialize(EntryProperties& properties) const override;
    void Deserialize(const EntryProperties& properties) override;

private:
    bool _override{ false };
    vsg::dvec3 _position;
    vsg::dquat _orientation;
    vsg::dvec3 _scale;
    std::weak_ptr<Entry> _root;
    EntryPath _path;
};
