#pragma once

// #include "Entry.h"
//#include "IReferenced.h"
// #include <vsg/all.h>
#include "IGeometryEntry.h"
//
//class DirectoryEntry;
//
//class GeometryEntry : public Entry {
//public:
//  GeometryEntry();
//  GeometryEntry(const GeometryEntry &entry);
//
//  EntryType GetType() const override;
//  virtual vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() = 0;
//  std::shared_ptr<Entry> FindEntry(const EntryPath &path) const override;
//
//  std::shared_ptr<Entry> CreateView(std::shared_ptr<AsyncQueue> sync) override;
//};
//
//class GeometryPackageEntry final : public GeometryEntry {
//public:
//  GeometryPackageEntry(vsg::ref_ptr<vsg::VertexIndexDraw> indexedGeometry)
//      : _geometry{indexedGeometry} {}
//
//  GeometryPackageEntry() {}
//
//  vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override;
//  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
//
//protected:
//  void CloneFrom(std::shared_ptr<Entry> entry) override;
//  std::shared_ptr<Entry> CreateCopy() const override;
//
//private:
//  vsg::ref_ptr<vsg::VertexIndexDraw> _geometry;
//};
//
//class GeometryProxyEntry final : public GeometryEntry {
//public:
//  GeometryProxyEntry(EntryPath path);
//  GeometryProxyEntry() {}
//
//  vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override;
//  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
//
//  void Serialize(EntryProperties &properties) const override;
//  void DeserializeInternal(EntryPath path,
//                           const EntryProperties &properties) override;
//
//protected:
//  void CloneFrom(std::shared_ptr<Entry> entry) override;
//  std::shared_ptr<Entry> CreateCopy() const override;
//
//private:
//  EntryPath _path;
//};
//
//class GeometryEntryView final : public GeometryEntry {
//public:
//  GeometryEntryView(std::shared_ptr<GeometryEntry> model,
//                    std::shared_ptr<AsyncQueue> sync)
//      : _model{model}, _sync{sync} {}
//
//  GeometryEntryView() {}
//
//  vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override;
//  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
//
//protected:
//  void CloneFrom(std::shared_ptr<Entry> entry) override;
//  std::shared_ptr<Entry> CreateCopy() const override;
//
//private:
//  std::shared_ptr<GeometryEntry> _model;
//  std::shared_ptr<AsyncQueue> _sync;
//};