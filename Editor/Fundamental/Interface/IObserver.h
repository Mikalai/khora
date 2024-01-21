#pragma once

#include <Fundamental/Interface/IError.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka {
namespace Fundamental {

class IObserver : public Fundamental::IReferenced {
public:
  virtual void OnNext(Ref<IMessage> msg) = 0;
  virtual void OnError(Ref<IError> error) = 0;
  virtual void OnComplete() = 0;
};
template <> struct GetIID<IObserver> {
  static constexpr InterfaceId Id = {{0xed, 0x6b, 0xd4, 0x2c, 0xa1, 0x43, 0x49,
                                      0x3, 0xb5, 0xc3, 0x7a, 0x89, 0x16, 0xc6,
                                      0x2d, 0x99}};
};
class IObservable : public Fundamental::IReferenced {
public:
  virtual Ref<IReferenced> Subscribe(Ref<IObserver> value) = 0;
};
template <> struct GetIID<IObservable> {
  static constexpr InterfaceId Id = {{0x1e, 0x94, 0x30, 0xd9, 0x65, 0xfa, 0x44,
                                      0x87, 0x89, 0x2b, 0xd7, 0x78, 0x57, 0x49,
                                      0xd5, 0x16}};
};
} // namespace Fundamental

using Fundamental::IObservable;
using Fundamental::IObserver;

} // namespace Vandrouka
