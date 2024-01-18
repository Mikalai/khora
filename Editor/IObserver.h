#pragma once

#include <boost/uuid/uuid_hash.hpp>
#include <span>
#include "Errors.h"
#include "IReferenced.h"

namespace Vandrouka {

using MessageId = boost::uuids::uuid;

class IMessage : public IReferenced {
public:
  virtual const MessageId& GetTypeID() const = 0;
};

template <typename T>
concept MessageType = requires(T a) {
  { std::derived_from<T, IMessage> };
};

template <> struct GetIID<IMessage> {
  static constexpr InterfaceId Id = {{0xad, 0x15, 0xcd, 0x2b, 0xe4, 0x2b, 0x43,
                                      0xef, 0x8f, 0x74, 0x5d, 0x2f, 0x9a, 0xb1,
                                      0xce, 0x5}};
};


class IMessageOutput : public IReferenced {
public:
  virtual void SubmitMessage(Ref<IMessage> msg) = 0;
  virtual void SubmitError(Ref<IError> msg) = 0;

  void SubmitAllMessages(auto container) {
    for (auto it = std::begin(container); it != std::end(container); ++it) {
      SubmitMessage(*it);
    }
  }
};

template <> struct GetIID<IMessageOutput> {
  static constexpr InterfaceId Id = {{0x63, 0x3e, 0x6c, 0x85, 0xe1, 0xda, 0x41,
                                      0x74, 0x93, 0xcf, 0x4c, 0x14, 0xf7, 0x21,
                                      0xb2, 0x3}};
};

class IMessageProcessor : public IReferenced {
public:
  virtual std::span<MessageId> GetMessageIds() = 0;
  virtual void Process(Ref<IReferenced> state, Ref<IMessage> msg,
                       Ref<IMessageOutput> sink) = 0;
};

template <> struct GetIID<IMessageProcessor> {
  static constexpr InterfaceId Id = {{0x3b, 0xc2, 0x63, 0xc5, 0x16, 0x64, 0x42,
                                      0x9, 0x9c, 0x28, 0x1b, 0xe2, 0x38, 0x84,
                                      0xbe, 0x4f}};
};

class IAggregatedProcessor : public IMessageProcessor {
public:
  virtual void AddProcessor(Ref<IMessageProcessor> processor) = 0;
  virtual void SetUnhandledProcessor(Ref<IMessageProcessor> processor) = 0;
};

template <> struct GetIID<IAggregatedProcessor> {
  static constexpr InterfaceId Id = {{0x3e, 0x14, 0x3, 0xdb, 0x8e, 0xbc, 0x44,
                                      0x61, 0x9f, 0x6, 0x7e, 0x91, 0xc4, 0x88,
                                      0x3, 0xd1}};
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
