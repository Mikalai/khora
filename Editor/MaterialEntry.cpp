#include <vsg/all.h>

#include "DirectoryEntry.h"
#include "IPackageEntry.h"
#include "MaterialEntry.h"

#include <magic_enum.hpp>

#include "AsyncQueue.h"
#include "Clone.h"
#include "ProxyEntry.h"
#include "Serializer.h"

namespace Vandrouka {

template <typename Derived, typename... I>
class MaterialEntry : public DirectoryEntryBase<Derived, IMaterialEntry, I...> {
public:
  EntryType GetType() const override { return EntryType::Material; }
  virtual Result<vsg::ref_ptr<vsg::StateGroup>> GetState() const = 0;
  // virtual std::shared_ptr<Entry>
  // CreateView(std::shared_ptr<AsyncQueue> sync) override;

protected:
  // bool CanAdd(std::shared_ptr<Entry>) final { return true; }
};

class MaterialPackageEntry
    : public MaterialEntry<MaterialPackageEntry, IPackageEntry> {
public:
  Result<vsg::ref_ptr<vsg::StateGroup>> GetState() const override { return ::Clone(_state); }

  vsg::ref_ptr<vsg::Object> GetData() const override { return ::Clone(_state); }

  Ref<IPackageEntry> SetData(vsg::ref_ptr<vsg::Object> data) override {
    _state = data.cast<vsg::StateGroup>();
    return {this};
  }

protected:
  // void CloneFrom(std::shared_ptr<Entry> entry) override;
  // std::shared_ptr<Entry> CreateCopy() const override;

private:
  vsg::ref_ptr<vsg::StateGroup> _state;
};

IReferenced *CreateMaterialPackageEntry() {
  static_assert(std::is_base_of_v<IReferenced, MaterialPackageEntry>);
  static_assert(std::is_base_of_v<IMaterialEntry, MaterialPackageEntry>);
  return static_cast<IMaterialEntry *>(new MaterialPackageEntry());
}

class MaterialProxyEntry
    : public ProxyEntry <
      MaterialProxyEntry, MaterialEntry> {
public:

  Result<vsg::ref_ptr<vsg::StateGroup>> GetState() const override {
    auto root = GetRoot().Cast<IDirectoryEntry>();
    if (!root)
      throw std::runtime_error(
          "Proxy material references object in the catalog that doesn't "
          "exist.");

    if (auto entry = root->FindEntry(GetPath()); entry) {
      if (auto transform = entry.Cast<IMaterialEntry>(); transform) {
        return transform->GetState();
      } else {
        return {new GenericError(LOG_LEVEL_ERROR, LOG_TYPE_MISMATCH,
                                 std::string("MaterialProxyEntry"))};
      }
    } else {
      return {new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND,
                               GetPath().Path)};
    }
  }
};

IReferenced *CreateMaterialProxyEntry() {
  static_assert(std::is_base_of_v<IReferenced, MaterialProxyEntry>);
  static_assert(std::is_base_of_v<IMaterialEntry, MaterialProxyEntry>);
  return static_cast<IMaterialEntry *>(new MaterialProxyEntry());
}

class MaterialEntryView : public MaterialEntry<MaterialEntryView> {
public:
  // MaterialEntryView(std::shared_ptr<MaterialEntry> entry,
  //                   std::shared_ptr<AsyncQueue> sync)
  //     : _model{entry}, _sync{sync} {}

  MaterialEntryView() {}

  Result<vsg::ref_ptr<vsg::StateGroup>> GetState() const override;
  // std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

protected:
  // void CloneFrom(std::shared_ptr<Entry> entry) override;
  // std::shared_ptr<Entry> CreateCopy() const override;

private:
  Ref<IMaterialEntry> _model;
  mutable Ref<IAsyncQueue> _sync;
};
} // namespace Vandrouka

// MaterialEntry::MaterialEntry() {}
//
// EntryType MaterialEntry::GetType() const { return EntryType::Material; }
//
// std::shared_ptr<Entry>
// MaterialEntry::CreateView(std::shared_ptr<AsyncQueue> sync) {
//   assert(std::dynamic_pointer_cast<MaterialEntry>(shared_from_this()));
//   return std::make_shared<MaterialEntryView>(
//       std::static_pointer_cast<MaterialEntry>(shared_from_this()), sync);
// }
//
// vsg::ref_ptr<vsg::StateGroup> MaterialPackageEntry::GetState() const {
//   return ::Clone(_state);
// }
//
// std::shared_ptr<Entry> MaterialPackageEntry::CreateProxy(EntryPath path) {
//   return std::make_shared<MaterialProxyEntry>(path);
// }
//
// void MaterialPackageEntry::CloneFrom(std::shared_ptr<Entry> entry) {
//   MaterialEntry::CloneFrom(entry);
//   assert(std::dynamic_pointer_cast<MaterialPackageEntry>(entry));
//   auto e = std::static_pointer_cast<MaterialPackageEntry>(entry);
//   this->_state = e->_state;
// }
//
// std::shared_ptr<Entry> MaterialPackageEntry::CreateCopy() const {
//   return std::make_shared<MaterialPackageEntry>();
// }
//
// MaterialProxyEntry::MaterialProxyEntry(EntryPath path) : _path{path} {}
//
// vsg::ref_ptr<vsg::StateGroup> MaterialProxyEntry::GetState() const {
//   auto root = GetRoot();
//   if (!root)
//     throw std::runtime_error(
//         "Proxy material references object in the catalog that doesn't "
//         "exist.");
//
//   if (auto entry = root->FindEntry(_path); entry) {
//     if (auto transform = std::dynamic_pointer_cast<MaterialEntry>(entry);
//         transform) {
//       return transform->GetState();
//     } else {
//       const_cast<MaterialProxyEntry &>(*this).OnError(
//           LogError(LOG_TYPE_MISMATCH));
//       return {};
//     }
//   } else {
//     const_cast<MaterialProxyEntry &>(*this).OnError(
//         LogError(LOG_ENTRY_NOT_FOUND, this->_path.Path));
//     return {};
//   }
// }
//
// std::shared_ptr<Entry> MaterialProxyEntry::CreateProxy(EntryPath) {
//   return std::make_shared<MaterialProxyEntry>(_path);
// }
//
// void MaterialProxyEntry::Serialize(EntryProperties &properties) const {
//   MaterialEntry::Serialize(properties);
//   properties["Path"] = _path.Path;
// }
//
// void MaterialProxyEntry::DeserializeInternal(
//     EntryPath path, const EntryProperties &properties) {
//   MaterialEntry::DeserializeInternal(path, properties);
//   _path.Path = ::Deserialize(properties, "Path", std::string{});
// }
//
// void MaterialProxyEntry::CloneFrom(std::shared_ptr<Entry> entry) {
//   MaterialEntry::CloneFrom(entry);
//   assert(std::dynamic_pointer_cast<MaterialProxyEntry>(entry));
//   auto e = std::static_pointer_cast<MaterialProxyEntry>(entry);
//   this->_path = e->_path;
// }
//
// std::shared_ptr<Entry> MaterialProxyEntry::CreateCopy() const {
//   return std::make_shared<MaterialProxyEntry>();
// }
//
// vsg::ref_ptr<vsg::StateGroup> MaterialEntryView::GetState() const {
//   return _sync->Execute([&]() { return _model->GetState(); });
// }
//
// std::shared_ptr<Entry> MaterialEntryView::CreateProxy(EntryPath path) {
//   return _sync->Execute([&]() { return _model->CreateProxy(path); });
// }
//
// void MaterialEntryView::CloneFrom(std::shared_ptr<Entry> entry) {
//   MaterialEntry::CloneFrom(entry);
//   assert(std::dynamic_pointer_cast<MaterialEntryView>(entry));
//   auto e = std::static_pointer_cast<MaterialEntryView>(entry);
//
//   this->_model = e->_model;
//   this->_sync = e->_sync;
// }
//
// std::shared_ptr<Entry> MaterialEntryView::CreateCopy() const {
//   return std::make_shared<MaterialEntryView>(this->_model, this->_sync);
// }
