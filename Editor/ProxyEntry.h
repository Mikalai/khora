#pragma once

#include "IProxyEntry.h"
#include "Entry.h"
#include "ISerializable.h"

namespace Vandrouka {

template <typename Derived, template <typename...> typename Parent,
          typename... Interfaces>
class ProxyEntry : public Parent<Derived, Interfaces..., IProxyEntry> {
  using Base = Parent<Derived, Interfaces..., IProxyEntry>;

public:
  void SetPath(EntryPath path) override { _path = path; }
  EntryPath GetPath() const override { return _path; }

  Result<Ref<IPackageReader>>
  DeserializeInternal(Ref<IEntryPathStateWrapper> state,
                      Ref<IPackageReader> reader) override {

    Base::DeserializeInternal(state, reader);

    _path.Path = reader->ReadString("Path").Value();

    return reader;
  }

  Result<Ref<IPackageWriter>>
  SerializeInternal(Ref<IPackageWriter> writer) const override {
    Base::SerializeInternal(writer);
    writer->Write("Path", _path.Path);
    return {writer};
  }

private:
  EntryPath _path;
};

} // namespace Vandrouka
