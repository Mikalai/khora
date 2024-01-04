#include "IAsyncQueue.h"
#include "IConfigEntry.h"
#include "IGroupEntry.h"
#include "ILocalizedEntry.h"
#include "IReferenced.h"
#include "ISystemFonts.h"
#include "ITextEntry.h"
#include "ITransformEntry.h"

namespace Vandrouka {

IReferenced *CreateAsyncQueue();
IReferenced *CreateSystemFonts();
IReferenced *CreateGroupEntry();
IReferenced *CreateTextEntry();
IReferenced *CreateTransformProxyEntry();
IReferenced *CreateLocalizedEntry();
IReferenced *CreateConfigEntry();

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
  } else {
    result = nullptr;
  }

  if (result) {
    return result->QueryInterface(iid, obj);
  }

  return false;
}

} // namespace Vandrouka
