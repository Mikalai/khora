#include <magic_enum.hpp>
#include <vsg/all.h>

#include <Catalog/Interface/IPackageEntry.h>
#include <Fundamental/Module/AsyncQueue.h>
#include <Serializer/Interface/ISerializable.h>

#include "Clone.h"
#include "DirectoryEntry.h"
#include "GeometryEntry.h"
#include "ProxyEntry.h"

namespace Vandrouka::Catalog::Private {

template <typename Derived, typename... I>
class GeometryEntry
    : public EntryBase<Derived, IGeometryEntry, I..., IEntry, Serializer::ISerializable> {

public:
  EntryType GetType() const override { return EntryType::Geometry; }

  virtual vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() = 0;
};

class GeometryPackageEntry final
    : public GeometryEntry<GeometryPackageEntry, IPackageEntry> {
public:
  using Interfaces =
      Fundamental::Private::QueryInterfaces<GeometryPackageEntry, IGeometryEntry, IPackageEntry,
                      IEntry, Serializer::ISerializable, IReferenced>;

  vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override {
    return ::Clone(_geometry);
  }

  vsg::ref_ptr<vsg::Object> GetData() const override {
    return ::Clone(_geometry);
  }

  Ref<IPackageEntry> SetData(vsg::ref_ptr<vsg::Object> data) override {
    _geometry = data.cast<vsg::VertexIndexDraw>();
    return {this};
  }

private:
  vsg::ref_ptr<vsg::VertexIndexDraw> _geometry;
};

class GeometryProxyEntry final
    : public ProxyEntry<GeometryProxyEntry, GeometryEntry> {
  //
  // public:
  //  void SetPath(EntryPath path) override { _path = path; }
  //  EntryPath GetPath() const override { return _path; }
  //
  vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override {
    auto root = GetRoot().Cast<IDirectoryEntry>();
    if (!root)
      throw std::runtime_error("Proxy geometry references object in the "
                               "catalog that doesn't exist.");

    if (auto entry = root->FindEntry(GetPath()); entry) {
      if (auto transform = entry.Cast<IGeometryEntry>(); transform) {
        return transform->GetGeometry();
      } else {
        throw std::runtime_error(
            std::string("Proxy geometry references wrong object of type ")
                .append(magic_enum::enum_name(entry->GetType())));
      }
    } else {
      throw std::runtime_error(
          "Proxy geometry references object that doesn't exist.");
    }
  }
  //
  // private:
  //  EntryPath _path;
};
//
//class GeometryEntryView final : public GeometryEntry<GeometryEntryView> {
//public:
//  /*GeometryEntryView(std::shared_ptr<GeometryEntry> model,
//                    std::shared_ptr<AsyncQueue> sync)
//      : _model{model}, _sync{sync} {}*/
//
//  // GeometryEntryView() {}
//
//  vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry() override;
//  // std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
//
//protected:
//  // void CloneFrom(std::shared_ptr<Entry> entry) override;
//  // std::shared_ptr<Entry> CreateCopy() const override;
//
//private:
//  std::shared_ptr<GeometryEntry> _model;
//  std::shared_ptr<Fundamental::Private::AsyncQueue> _sync;
//};

} // namespace Vandrouka::Catalog::Private

namespace Vandrouka::Factory {

IReferenced *CreateGeometryProxyEntry() {
  static_assert(
      std::is_base_of_v<IReferenced, Catalog::Private::GeometryProxyEntry>);
  return static_cast<Catalog::IGeometryEntry *>(
      new Catalog::Private::GeometryProxyEntry());
}

IReferenced *CreateGeometryPackageEntry() {
  static_assert(
      std::is_base_of_v<IReferenced, Catalog::Private::GeometryPackageEntry>);
  return static_cast<Catalog::IGeometryEntry *>(
      new Catalog::Private::GeometryPackageEntry());
}

} // namespace Vandrouka::Factory

// GeometryEntry::GeometryEntry() {}
//
// GeometryEntry::GeometryEntry(const GeometryEntry &entry) : Entry{entry} {}
//
// EntryType GeometryEntry::GetType() const { return EntryType::Geometry; }
//
// vsg::ref_ptr<vsg::VertexIndexDraw> GeometryPackageEntry::GetGeometry() {
//   return ::Clone(_geometry);
// }
//
// std::shared_ptr<Entry> GeometryPackageEntry::CreateProxy(EntryPath path) {
//   return std::make_shared<GeometryProxyEntry>(path);
// }
//
// void GeometryPackageEntry::CloneFrom(std::shared_ptr<Entry> entry) {
//   GeometryEntry::CloneFrom(entry);
//   assert(std::dynamic_pointer_cast<GeometryPackageEntry>(entry));
//   auto e = std::static_pointer_cast<GeometryPackageEntry>(entry);
//   this->_geometry = e->_geometry;
// }
//
// std::shared_ptr<Entry> GeometryPackageEntry::CreateCopy() const {
//   return std::make_shared<GeometryPackageEntry>();
// }
//
// std::shared_ptr<Entry> GeometryEntry::FindEntry(const EntryPath &) const {
//   return {};
// }
//
// std::shared_ptr<Entry>
// GeometryEntry::CreateView(std::shared_ptr<AsyncQueue> sync) {
//   assert(std::dynamic_pointer_cast<GeometryEntry>(shared_from_this()));
//   return std::make_shared<GeometryEntryView>(
//       std::static_pointer_cast<GeometryEntry>(shared_from_this()), sync);
// }
//
// GeometryProxyEntry::GeometryProxyEntry(EntryPath path) : _path{path} {}
//
// vsg::ref_ptr<vsg::VertexIndexDraw> GeometryProxyEntry::GetGeometry() {
//   auto root = GetRoot();
//   if (!root)
//     throw std::runtime_error(
//         "Proxy geometry references object in the catalog that doesn't
//         exist.");
//
//   if (auto entry = root->FindEntry(_path); entry) {
//     if (auto transform = std::dynamic_pointer_cast<GeometryEntry>(entry);
//         transform) {
//       return transform->GetGeometry();
//     } else {
//       throw std::runtime_error(
//           std::string("Proxy geometry references wrong object of type ")
//               .append(magic_enum::enum_name(entry->GetType())));
//     }
//   } else {
//     throw std::runtime_error(
//         "Proxy geometry references object that doesn't exist.");
//   }
// }
//
// std::shared_ptr<Entry> GeometryProxyEntry::CreateProxy(EntryPath path) {
//   return std::make_shared<GeometryProxyEntry>(path);
// }
//
// void GeometryProxyEntry::Serialize(EntryProperties &properties) const {
//   GeometryEntry::Serialize(properties);
//   properties["Path"] = _path.Path;
// }
//
// void GeometryProxyEntry::DeserializeInternal(
//     EntryPath path, const EntryProperties &properties) {
//   GeometryEntry::DeserializeInternal(path, properties);
//   _path.Path = ::Deserialize(properties, "Path", std::string{});
// }
//
// void GeometryProxyEntry::CloneFrom(std::shared_ptr<Entry> entry) {
//   GeometryEntry::CloneFrom(entry);
//   assert(std::dynamic_pointer_cast<GeometryProxyEntry>(entry));
//   auto e = std::static_pointer_cast<GeometryProxyEntry>(entry);
//   this->_path = e->_path;
// }
//
// std::shared_ptr<Entry> GeometryProxyEntry::CreateCopy() const {
//   return std::make_shared<GeometryProxyEntry>();
// }
//
// vsg::ref_ptr<vsg::VertexIndexDraw> GeometryEntryView::GetGeometry() {
//   return _sync->Execute([&]() { return _model->GetGeometry(); });
// }
//
// std::shared_ptr<Entry> GeometryEntryView::CreateProxy(EntryPath path) {
//   return _sync->Execute([&]() { return _model->CreateProxy(path); });
// }
//
// void GeometryEntryView::CloneFrom(std::shared_ptr<Entry> entry) {
//   GeometryEntry::CloneFrom(entry);
//   assert(std::dynamic_pointer_cast<GeometryEntryView>(entry));
//   auto e = std::static_pointer_cast<GeometryEntryView>(entry);
//   this->_model = e->_model;
//   this->_sync = e->_sync;
// }
//
// std::shared_ptr<Entry> GeometryEntryView::CreateCopy() const {
//   return std::make_shared<GeometryEntryView>();
// }
