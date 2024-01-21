#pragma once

#include <boost/uuid/uuid.hpp>
#include <functional>
#include <magic_enum.hpp>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string_view>
#include <vector>

#include <Catalog/Interface/EntryPath.h>
#include <Catalog/Interface/EntryType.h>
#include <Catalog/Interface/IEntry.h>
#include <Fundamental/Module/Observer.h>
#include <Fundamental/Module/Referenced.h>
#include <Serializer/Interface/ISerializable.h>

CREATE_STATE_WRAPPER(Vandrouka::Catalog, EntryPath, 0xbf, 0x18, 0xd2, 0x4, 0x3,
                     0xc6, 0x4a, 0xb3, 0x82, 0x7b, 0xdd, 0x8d, 0x36, 0x5, 0xae,
                     0x3a);

namespace Vandrouka::Catalog::Private {

template <typename Derived, typename... I>
class EntryBase
    : public Fundamental::Private::ReferenceCountedBase<Derived, I...> {

public:
  using Interfaces = Fundamental::Private::QueryInterfaces<
      Derived, I..., IEntry, Serializer::ISerializable, IReferenced>;

  using Base = Fundamental::Private::ReferenceCountedBase<Derived, I...>;

public:
  EntryRef GetParent() const override { return this->_parent; }

  void SetParent(IEntry *parent) override {
    // do not increase references. TODO: Add weak references support.
    this->_parent = parent;
  }

  EntryRef GetRoot() const override {
    Ref<IEntry> root{(IEntry *)this};
    auto next = root->GetParent();

    while (next) {
      root = next;
      next = root->GetParent();
    }

    return root;
  }

  Result<Ref<Serializer::IPackageWriter>>
  Serialize(Ref<Serializer::IPackageWriter> package,
            Ref<IReferenced> state) const override {
    return SerializeInternal(package);
  }

  Result<Ref<Serializer::IPackageReader>>
  Deserialize(Ref<Serializer::IPackageReader> package,
              Ref<IReferenced> state) override {
    EntryPath path{};
    if (!state) {
      state = new EntryPathStateWrapper{&path};
    }
    return DeserializeInternal(state, package);
  }

  virtual Result<Ref<Serializer::IPackageWriter>>
  SerializeInternal(Ref<Serializer::IPackageWriter> writer) const {
    writer->Write("Type", std::string(magic_enum::enum_name(this->GetType())));
    return writer;
  }

  virtual Result<Ref<Serializer::IPackageReader>>
  DeserializeInternal(Ref<IEntryPathStateWrapper> path,
                      Ref<Serializer::IPackageReader> reader) {
    return reader;
  }

private:
  IEntry *_parent{nullptr};
};

} // namespace Vandrouka::Catalog::Private
