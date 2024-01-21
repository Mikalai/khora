
#include <magic_enum.hpp>

#include "Clone.h"
#include "DirectoryEntry.h"
#include "Errors.h"
#include "TransformEntry.h"
#include <Catalog/Interface/IProxyEntry.h>
#include <Fundamental/Module/AsyncQueue.h>
#include <Serializer/Interface/ISerializable.h>

namespace Vandrouka::Catalog::Private {

class TransformProxyEntry final
    : public DirectoryEntryBase<TransformProxyEntry, ITransformEntry,
                                IProxyEntry> {

  using Base =
      DirectoryEntryBase<TransformProxyEntry, ITransformEntry, IProxyEntry>;

public:
  EntryType GetType() const override { return EntryType::Transform; }

  vsg::dmat4 GetWorldMatrix() override {
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> path;
    path.push_back(GetTransform().Value());
    auto parent = GetParent().Cast<IDirectoryEntry>();

    while (parent) {
      if (auto tr = parent.Cast<ITransformEntry>(); tr) {
        path.push_back(tr->GetTransform().Value());
      }
      parent = parent->GetParent().Cast<IDirectoryEntry>();
    }

    vsg::dmat4 r;

    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      r = r * (*it)->matrix;
    }

    return r;
  }

  Result<vsg::ref_ptr<vsg::MatrixTransform>> GetTransform() const override {
    auto root = GetRoot().Cast<IDirectoryEntry>();
    if (!root) {
      return CreateError(LOG_ENTRY_NOT_FOUND, this->_path.Path);
    }

    if (_override || !_path.IsValid()) {
      vsg::ref_ptr<vsg::MatrixTransform> transform =
          vsg::MatrixTransform::create();
      transform->matrix = vsg::translate(_position) *
                          vsg::rotate(_orientation) * vsg::scale(_scale);
      return transform;
    } else {
      if (auto entry = root->FindEntry(_path); entry) {
        if (auto transform = entry.Cast<ITransformEntry>(); transform) {
          return transform->GetTransform();
        } else {
          return CreateError(LOG_TYPE_MISMATCH, this->_path.Path);
        }
      } else {
        return CreateError(LOG_ENTRY_NOT_FOUND, this->_path.Path);
      }
    }
  }

  void SetOverride(bool flag) {
    if (_override == flag)
      return;

    _override = flag;
    // OnPropertyChanged("Override");
  }

  bool GetOverride() const override { return _override; }

  void SetPosition(vsg::dvec3 value) {
    if (_position == value)
      return;

    _position = value;
    // OnPropertyChanged("Position");
  }

  vsg::dvec3 GetPosition() const override { return _position; }

  void SetScale(vsg::dvec3 value) {
    if (_scale == value)
      return;

    _scale = value;
    // OnPropertyChanged("Scale");
  }

  vsg::dvec3 GetScale() const override { return _scale; }

  void SetOrientation(vsg::dquat value) {
    if (_orientation == value)
      return;

    _orientation = value;
    // OnPropertyChanged("Orientation");
  }

  vsg::dquat GetOrientation() const override { return _orientation; }

  bool IsMutable() const override { return true; }

  Result<Ref<Serializer::IPackageWriter>>
  SerializeInternal(Ref<Serializer::IPackageWriter> writer) const override {
    Base::SerializeInternal(writer);

    writer->Write("Override", _override);
    writer->WriteVector3D("Position", _position.x, _position.y, _position.z);
    writer->WriteVector4D("Orientation", _orientation.x, _orientation.y,
                          _orientation.z, _orientation.w);
    writer->WriteVector3D("Scale", _scale.x, _scale.y, _scale.z);
    writer->Write("Path", _path.Path);

    return writer;
  }

  Result<Ref<Serializer::IPackageReader>>
  DeserializeInternal(Ref<IEntryPathStateWrapper> state,
                      Ref<Serializer::IPackageReader> reader) override {

    Base::DeserializeInternal(state, reader);

    _override = reader->ReadBool("Override").Value(false);
    {
      auto [x, y, z] = reader->ReadVector3D("Position").Value({});
      _position.set(x, y, z);
    }
    {
      auto [x, y, z, w] = reader->ReadVector4D("Orientation").Value({});
      _orientation.set(x, y, z, w);
    }
    {
      auto [x, y, z] = reader->ReadVector3D("Scale").Value({});
      _scale.set(x, y, z);
    }

    _path.Path = reader->ReadString("Path").Value({});

    return reader;
  }

private:
  bool _override{false};
  vsg::dvec3 _position;
  vsg::dquat _orientation;
  vsg::dvec3 _scale{1, 1, 1};
  EntryPath _path;

  // Inherited via DirectoryEntryBase
  void SetPath(EntryPath path) override { _path = path; }

  //  Ref<IEntry> CreateProxy(EntryPath path) override { return Ref<IEntry>(); }

  EntryPath GetPath() const override { return _path; }
};

} // namespace Vandrouka::Catalog::Private

namespace Vandrouka::Factory {

IReferenced *CreateTransformProxyEntry() {
  static_assert(
      std::is_base_of_v<IReferenced, Catalog::Private::TransformProxyEntry>);
  static_assert(std::is_base_of_v<Catalog::ITransformEntry,
                                  Catalog::Private::TransformProxyEntry>);
  return static_cast<Catalog::ITransformEntry *>(
      new Catalog::Private::TransformProxyEntry());
}

} // namespace Vandrouka::Factory