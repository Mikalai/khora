#include <vsg/all.h>

#include <magic_enum.hpp>

#include <Catalog/Interface/IPackageEntry.h>

#include "Clone.h"
#include "DirectoryEntry.h"
#include "MaterialEntry.h"
#include "ProxyEntry.h"
#include <Serializer/Interface/ISerializable.h>

namespace Vandrouka::Catalog::Private {

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
  Result<vsg::ref_ptr<vsg::StateGroup>> GetState() const override {
    return ::Clone(_state);
  }

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

class MaterialProxyEntry
    : public ProxyEntry<MaterialProxyEntry, MaterialEntry> {
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
        return CreateError(LOG_TYPE_MISMATCH,
                           std::string("MaterialProxyEntry"));
      }
    } else {
      return CreateError(LOG_ENTRY_NOT_FOUND, GetPath().Path);
    }
  }
};

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
} // namespace Vandrouka::Catalog::Private

namespace Vandrouka::Factory {

IReferenced *CreateMaterialPackageEntry() {
  static_assert(
      std::is_base_of_v<IReferenced, Catalog::Private::MaterialPackageEntry>);
  static_assert(std::is_base_of_v<Catalog::IMaterialEntry,
                                  Catalog::Private::MaterialPackageEntry>);
  return static_cast<Catalog::IMaterialEntry *>(
      new Catalog::Private::MaterialPackageEntry());
}

IReferenced *CreateMaterialProxyEntry() {
  static_assert(
      std::is_base_of_v<IReferenced, Catalog::Private::MaterialProxyEntry>);
  static_assert(std::is_base_of_v<Catalog::IMaterialEntry,
                                  Catalog::Private::MaterialProxyEntry>);
  return static_cast<Catalog::IMaterialEntry *>(
      new Catalog::Private::MaterialProxyEntry());
}

} // namespace Vandrouka::Factory
