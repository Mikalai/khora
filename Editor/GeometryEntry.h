#pragma once

#include <vsg/all.h>
#include "Entry.h"

class DirectoryEntry;

class GeometryEntry : public Entry {
public:
    EntryType GetType() const override;
    virtual vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() = 0;
    std::shared_ptr<Entry> FindEntry(const EntryPath& path) const override;
};

class GeometryPackageEntry final : public GeometryEntry {
public:
    
    GeometryPackageEntry(vsg::ref_ptr<vsg::VertexIndexDraw> indexedGeometry)
        : _geometry{ indexedGeometry } {
    }

    std::shared_ptr<Entry> Clone() override;
    vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override;
    std::shared_ptr<Entry> CreateProxy(std::shared_ptr<Entry> root, EntryPath path) override;

private:
    vsg::ref_ptr<vsg::VertexIndexDraw> _geometry;
};

class GeometryProxyEntry final : public GeometryEntry {
public:

    GeometryProxyEntry(EntryPath path, std::shared_ptr<Entry> root);
    
    std::shared_ptr<Entry> Clone() override;
    vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override;
    std::shared_ptr<Entry> CreateProxy(std::shared_ptr<Entry> root, EntryPath path) override;

    void Serialize(EntryProperties& properties) const override;
    void Deserialize(const EntryProperties& properties) override;

private:
    EntryPath _path;
    std::weak_ptr<Entry> _root;
};
