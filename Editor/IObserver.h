#pragma once

#include "Errors.h"
#include "IReferenced.h"

namespace Vandrouka {

class IMessage : public IReferenced {
public:
};
template <> struct GetIID<IMessage> {
  static constexpr InterfaceId Id = {{0xad, 0x15, 0xcd, 0x2b, 0xe4, 0x2b, 0x43,
                                      0xef, 0x8f, 0x74, 0x5d, 0x2f, 0x9a, 0xb1,
                                      0xce, 0x5}};
};

class ISubscribedMessage : public IMessage {
public:
  virtual Ref<IReferenced> GetObservable() = 0;
};
template <> struct GetIID<ISubscribedMessage> {
  static constexpr InterfaceId Id = {{0xea, 0xdf, 0x78, 0xb8, 0x1e, 0xca, 0x45,
                                      0xad, 0x8f, 0xf1, 0x7, 0x4c, 0xa6, 0x56,
                                      0x27, 0x74}};
};

class IObserver : public IReferenced {
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
class IObservable : public IReferenced {
public:
  virtual Ref<IReferenced> Subscribe(Ref<IObserver> value) = 0;
};
template <> struct GetIID<IObservable> {
  static constexpr InterfaceId Id = {{0x1e, 0x94, 0x30, 0xd9, 0x65, 0xfa, 0x44,
                                      0x87, 0x89, 0x2b, 0xd7, 0x78, 0x57, 0x49,
                                      0xd5, 0x16}};
};

} // namespace Vandrouka
