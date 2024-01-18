#pragma once

#include "IObserver.h"

namespace Vandrouka {

class IDataModel : public IReferenced {
public:
  virtual void AddDependency(Ref<IReferenced> d) = 0;
  virtual void Execute(Ref<IMessage> msg) = 0;
};

template <> struct GetIID<IDataModel> {
  static constexpr InterfaceId Id = {{0xef, 0xd4, 0xa7, 0xe9, 0x9d, 0xd8, 0x49,
                                      0x39, 0xbc, 0xe4, 0xf5, 0x65, 0xc9, 0xb1,
                                      0x57, 0x58}};
};

class DataModel;
template <> struct GetCID<DataModel> {
  static constexpr ClassId Id = {{0xbc, 0xdf, 0xb7, 0xe7, 0x58, 0xa9, 0x46,
                                  0x11, 0x9f, 0xd8, 0x70, 0x99, 0x3e, 0x8, 0x24,
                                  0x70}};
};

} // namespace Vandrouka