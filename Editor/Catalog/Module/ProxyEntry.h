#pragma once

#include <Catalog/Interface/IProxyEntry.h>
#include <Serializer/Interface/ISerializable.h>

#include "EntryBase.h"

namespace Vandrouka::Catalog::Private {

template <typename Derived, template <typename...> typename Parent,
          typename... Interfaces>
class ProxyEntry : public Parent<Derived, Interfaces..., IProxyEntry> {
  using Base = Parent<Derived, Interfaces..., IProxyEntry>;

public:
  void SetPath(EntryPath path) override { _path = path; }
  EntryPath GetPath() const override { return _path; }

  Result<Ref<Serializer::IPackageReader>>
  DeserializeInternal(Ref<IEntryPathStateWrapper> state,
                      Ref<Serializer::IPackageReader> reader) override {

    Base::DeserializeInternal(state, reader);

    _path.Path = reader->ReadString("Path").Value();

    return reader;
  }

  Result<Ref<Serializer::IPackageWriter>>
  SerializeInternal(Ref<Serializer::IPackageWriter> writer) const override {
    Base::SerializeInternal(writer);
    writer->Write("Path", _path.Path);
    return {writer};
  }

private:
  EntryPath _path;
};

} // namespace Vandrouka
