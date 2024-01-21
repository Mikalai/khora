#include <Catalog/Interface/IConfigEntry.h>
#include <Catalog/Interface/IGeometryEntry.h>
#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Interface/ILocalizedEntry.h>
#include <Catalog/Interface/IMaterialEntry.h>
#include <Catalog/Interface/ITextEntry.h>
#include <Catalog/Interface/ITransformEntry.h>
#include <Fonts/Interface/ISystemFonts.h>
#include <Fundamental/Module/AsyncQueue.h>
#include <Fundamental/Interface/IReferenced.h>
#include <Serializer/Interface/ISerializable.h>
#include <State/Interface/IDataModel.h>

namespace Vandrouka::Fundamental {

bool Create(const ClassId &cid, const InterfaceId &iid, void **obj) {

  Ref<IReferenced> result;

  if (cid == GetCID<Instances::Fundamental::AsyncQueue>::Id) {
    result = Ref<IReferenced>{Factory::CreateAsyncQueue()};
  } else if (cid == GetCID<Instances::Fonts::SystemFonts>::Id) {
    result = Ref<IReferenced>{Factory::CreateSystemFonts()};
  } else if (cid == GetCID<Instances::Catalog::GroupEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateGroupEntry()};
  } else if (cid == GetCID<Instances::Catalog::TextEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateTextEntry()};
  } else if (cid == GetCID<Instances::Catalog::TransformProxyEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateTransformProxyEntry()};
  } else if (cid == GetCID<Instances::Catalog::LocalizedEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateLocalizedEntry()};
  } else if (cid == GetCID<Instances::Catalog::ConfigEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateConfigEntry()};
  } else if (cid == GetCID<Instances::Serializer::JsonPackage>::Id) {
    result = Ref<IReferenced>{Factory::CreateJsonPackage()};
  } else if (cid == GetCID<Instances::State::DataModel>::Id) {
    result = Ref<IReferenced>{Factory::CreateDataModel()};
  } else if (cid == GetCID<Instances::Catalog::GeometryPackageEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateGeometryPackageEntry()};
  } else if (cid == GetCID<Instances::Catalog::GeometryProxyEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateGeometryProxyEntry()};
  } else if (cid == GetCID<Instances::Catalog::TransformPackageEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateTransformPackageEntry()};
  } else if (cid == GetCID<Instances::Catalog::TransformProxyEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateTransformProxyEntry()};
  } else if (cid == GetCID<Instances::Catalog::MaterialProxyEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateMaterialProxyEntry()};
  } else if (cid == GetCID<Instances::Catalog::MaterialPackageEntry>::Id) {
    result = Ref<IReferenced>{Factory::CreateMaterialPackageEntry()};
  } else {
    result = nullptr;
  }

  if (result) {
    return result->QueryInterface(iid, obj);
  }

  return false;
}

} // namespace Vandrouka::Fundamental::Private
