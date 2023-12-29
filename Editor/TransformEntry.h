#pragma once

#include <vsg/all.h>

#include <semaphore>

#include "DirectoryEntry.h"

class AsyncQueue;

class TransformEntry : public DirectoryEntry {
   public:
    TransformEntry();
    TransformEntry(const TransformEntry& entry);

    virtual vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const = 0;
    EntryType GetType() const override;

    virtual void SetOverride(bool) {}
    virtual bool GetOverride() const { return false; }

    virtual void SetPosition(vsg::dvec3) {}
    virtual vsg::dvec3 GetPosition() const { return {}; }

    virtual void SetScale(vsg::dvec3) {}
    virtual vsg::dvec3 GetScale() const { return {1, 1, 1}; }

    virtual void SetOrientation(vsg::dquat) {}
    virtual vsg::dquat GetOrientation() const { return {}; }

    virtual bool IsMutable() const { return false; }
    virtual std::shared_ptr<Entry> CreateView(
        std::shared_ptr<AsyncQueue> sync) override;

    vsg::dmat4 GetWorldMatrix();

   protected:
    bool CanAdd(std::shared_ptr<Entry>) final { return true; }
};

class TransformPackageEntry final : public TransformEntry {
   public:
    TransformPackageEntry(vsg::ref_ptr<vsg::MatrixTransform> transform)
        : _transform{transform} {}

    TransformPackageEntry() {}

    vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const;
    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

   protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

   private:
    vsg::ref_ptr<vsg::MatrixTransform> _transform;
};

class TransformProxyEntry final : public TransformEntry {
   public:
    TransformProxyEntry(EntryPath path);
    TransformProxyEntry(){};

    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
    vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const override;

    void SetOverride(bool flag) override;
    bool GetOverride() const override { return _override; }

    void SetPosition(vsg::dvec3 value) override;
    vsg::dvec3 GetPosition() const override { return _position; }

    void SetScale(vsg::dvec3 value) override;
    vsg::dvec3 GetScale() const override { return _scale; }

    void SetOrientation(vsg::dquat value) override;
    vsg::dquat GetOrientation() const override { return _orientation; }

    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path,
                             const EntryProperties& properties) override;

    bool IsMutable() const override { return true; }

   protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

   private:
    bool _override{false};
    vsg::dvec3 _position;
    vsg::dquat _orientation;
    vsg::dvec3 _scale{1, 1, 1};
    EntryPath _path;
};

class TransformEntryView : public TransformEntry {
   public:
    TransformEntryView(std::shared_ptr<TransformEntry> dataModel,
                       std::shared_ptr<AsyncQueue> syncContext)
        : _model{dataModel}, _sync{syncContext} {
        SetParent(dataModel->GetParent());
    }

    TransformEntryView() {}

    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
    vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const override;

    void SetOverride(bool flag) override;
    bool GetOverride() const override;

    void SetPosition(vsg::dvec3 value) override;
    vsg::dvec3 GetPosition() const override;

    void SetScale(vsg::dvec3 value) override;
    vsg::dvec3 GetScale() const override;

    void SetOrientation(vsg::dquat value) override;
    vsg::dquat GetOrientation() const override;

    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path,
                             const EntryProperties& properties) override;

    bool IsMutable() const override;

   protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

   private:
    std::shared_ptr<TransformEntry> _model;
    std::shared_ptr<AsyncQueue> _sync;
};