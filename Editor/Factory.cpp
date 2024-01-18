#include "IAsyncQueue.h"
#include "IConfigEntry.h"
#include "IGroupEntry.h"
#include "ILocalizedEntry.h"
#include "IReferenced.h"
#include "ISystemFonts.h"
#include "ITextEntry.h"
#include "ITransformEntry.h"
#include "ISerializable.h"
#include "IDataModel.h"
#include "IGeometryEntry.h"
#include "IMaterialEntry.h"

namespace Vandrouka {

IReferenced *CreateAsyncQueue();
IReferenced *CreateSystemFonts();
IReferenced *CreateGroupEntry();
IReferenced *CreateTextEntry();
IReferenced *CreateTransformProxyEntry();
IReferenced *CreateLocalizedEntry();
IReferenced *CreateConfigEntry();
IReferenced *CreateJsonPackage();
IReferenced *CreateDataModel();
IReferenced *CreateGeometryPackageEntry();
IReferenced *CreateGeometryProxyEntry();
IReferenced *CreateTransformPackageEntry();
IReferenced *CreateTransformProxyEntry();
IReferenced *CreateMaterialProxyEntry();
IReferenced *CreateMaterialPackageEntry();

  bool Create(const ClassId &cid, const InterfaceId &iid, void **obj) {

  Ref<IReferenced> result;

  if (cid == GetCID<AsyncQueue>::Id) {
    result = Ref<IReferenced>{CreateAsyncQueue()};
  } else if (cid == GetCID<SystemFonts>::Id) {
    result = Ref<IReferenced>{CreateSystemFonts()};
  } else if (cid == GetCID<GroupEntry>::Id) {
    result = Ref<IReferenced>{CreateGroupEntry()};
  } else if (cid == GetCID<TextEntry>::Id) {
    result = Ref<IReferenced>{CreateTextEntry()};
  } else if (cid == GetCID<TransformProxyEntry>::Id) {
    result = Ref<IReferenced>{CreateTransformProxyEntry()};
  } else if (cid == GetCID<LocalizedEntry>::Id) {
    result = Ref<IReferenced>{CreateLocalizedEntry()};
  } else if (cid == GetCID<ConfigEntry>::Id) {
    result = Ref<IReferenced>{CreateConfigEntry()};
  } else if (cid == GetCID<JsonPackage>::Id) {
    result = Ref<IReferenced>{CreateJsonPackage()};
  } else if (cid == GetCID<DataModel>::Id) {
    result = Ref<IReferenced>{CreateDataModel()};
  } else if (cid == GetCID<GeometryPackageEntry>::Id) {
    result = Ref<IReferenced>{CreateGeometryPackageEntry()};
  } else if (cid == GetCID<GeometryProxyEntry>::Id) {
    result = Ref<IReferenced>{CreateGeometryProxyEntry()};
  } else if (cid == GetCID<TransformPackageEntry>::Id) {
    result = Ref<IReferenced>{CreateTransformPackageEntry()};
  } else if (cid == GetCID<TransformProxyEntry>::Id) {
    result = Ref<IReferenced>{CreateTransformProxyEntry()};
  } else if (cid == GetCID<MaterialProxyEntry>::Id) {
    result = Ref<IReferenced>{CreateMaterialProxyEntry()};
  } else if (cid == GetCID<MaterialPackageEntry>::Id) {
    result = Ref<IReferenced>{CreateMaterialPackageEntry()};
  } else {
    result = nullptr;
  }

  if (result) {
    return result->QueryInterface(iid, obj);
  }

  return false;
}

} // namespace Vandrouka
