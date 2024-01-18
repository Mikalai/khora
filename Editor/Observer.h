#pragma once

#include <boost/asio/io_context.hpp>
#include <functional>
#include <memory>
#include <vector>

#include "AsyncQueue.h"
#include "IAsyncQueue.h"
#include "IObserver.h"

namespace Vandrouka {

template <typename Derived, typename Interface>
class MessageBase : public ReferenceCountedBase<Derived, Interface, IToString> {
public:
  using Interfaces = QueryInterfaces<Derived, Interface, IMessage, IToString, IReferenced>;

  const MessageId &GetTypeID() const override { return GetIID<Interface>::Id; }

  std::string ToString() const override { return typeid(Derived).name(); }
};

template <typename Derived, typename... I>
class ObservableBase : public ReferenceCountedBase<Derived, I..., IObservable> {

  using Base = ReferenceCountedBase<Derived, I..., IObservable>;
  using SelfType = ObservableBase<Derived, I...>;

  class SubscribedMessage
      : public MessageBase<SubscribedMessage, ISubscribedMessage> {
  public:
    SubscribedMessage(Ref<IReferenced> observable) : _observable{observable} {}

    Ref<IReferenced> GetObservable() override { return _observable; }

  private:
    Ref<IReferenced> _observable;
  };

  class Subscription final
      : public ReferenceCountedBase<Subscription, IReferenced> {
  public:
    using Interfaces = QueryInterfaces<Subscription, IReferenced>;

    Subscription(Ref<Derived> self, Ref<IObserver> observer)
        : _self{self}, _observer{observer} {}

    virtual ~Subscription() { _self->Unsubscribe(_observer); }

  private:
    Ref<Derived> _self;
    Ref<IObserver> _observer;
  };

  friend class Subscription;

protected:
  ObservableBase() {
    this->_queue = Create<AsyncQueue, IAsyncQueue>();
    assert(this->_queue);
  }

  void ExecuteAsync(std::function<void()> cb) {
    this->_queue->Enqueue(new CallbackTask{cb});
  }

public:
  Ref<IReferenced> Subscribe(Ref<IObserver> value) override {
    assert(value);
    Ref<IAsyncTask> subscriptionTask{new CallbackTask{[this, value]() mutable {
      this->_observers.push_back(value);
      // value->OnNext(new SubscribedMessage{this->Self()});
    }}};

    this->_queue->Enqueue(subscriptionTask);

    return new Subscription(static_cast<Derived *>(this), value);
  }

  Ref<IAsyncQueue> GetSyncContext() { return this->_queue; }

  Ref<IReferenced> Self() {
    IReferenced *r;
    if (static_cast<Derived *>(this)->QueryInterface(GetIID<IReferenced>::Id,
                                                     (void **)&r)) {
      Ref<IReferenced> result{r};
      r->Release();
      return result;
    }
    return {};
  }

protected:
  void RaiseMessage(Ref<IMessage> value) const {
    std::for_each(this->_observers.begin(), this->_observers.end(),
                  [&](auto o) { o->OnNext(value); });
  }

  void RaiseError(Ref<IError> value) const {
    if (!value)
      return;

    std::for_each(this->_observers.begin(), this->_observers.end(),
                  [&](auto o) { o->OnError(value); });
  }

  void Unsubscribe(Ref<IObserver> value) {
    Ref<IAsyncTask> usubscriptionTask{new CallbackTask{[this, value]() {
      if (auto it =
              std::find_if(this->_observers.begin(), this->_observers.end(),
                           [&](auto v) { return v == value; });
          it != this->_observers.end()) {
        this->_observers.erase(it);
      }
    }}};

    this->_queue->Enqueue(usubscriptionTask);
  }

private:
  Ref<IAsyncQueue> _queue;
  std::vector<Ref<IObserver>> _observers;
};

class ObserverWrapper
    : public ReferenceCountedBase<ObserverWrapper, IObserver> {

public:
  ObserverWrapper(IObserver *wnd) : _wnd{wnd} {}

  void OnNext(Ref<IMessage> msg) override;
  void OnError(Ref<IError> error) override;
  void OnComplete() override;

private:
  IObserver *_wnd;
};

class MessageSinkWrapper
    : public ReferenceCountedBase<MessageSinkWrapper, IMessageOutput> {
public:
  MessageSinkWrapper(IMessageOutput *sink) : _sink{sink} {}
  void SubmitMessage(Ref<IMessage> msg) override;
  void SubmitError(Ref<IError> msg) override;

private:
  IMessageOutput *_sink;
};

} // namespace Vandrouka

class Subscription : public std::enable_shared_from_this<Subscription> {
public:
  Subscription(std::function<void()> onDelete) : _onDelete{onDelete} {}

  ~Subscription() {
    if (_onDelete) {
      _onDelete();
    }
  }

private:
  std::function<void()> _onDelete;
};

class Subscription;
using SubscriptionPtr = std::shared_ptr<Subscription>;

template <typename Derived, typename Observer, typename Interface>
class Observable : public Interface,
                   public std::enable_shared_from_this<
                       Observable<Derived, Observer, Interface>> {
public:
  Observable(std::shared_ptr<boost::asio::io_context> ctx) {
    (this->_queue = std::make_shared<AsyncQueue>(ctx))->Start();
  }

  [[nodiscard]] SubscriptionPtr
  Subscribe(std::shared_ptr<Observer> observer) override {
    assert(observer);

    this->_queue->Enqueue([&]() {
      this->_observers.push_back(observer);
      this->OnSubscribed(observer);
    });

    return std::make_shared<Subscription>([this, observer]() {
      this->_queue->Enqueue(
          [this, observer]() { this->RemoveSubscription(observer); });
    });
  }

  std::shared_ptr<AsyncQueue> GetSyncContext() override { return this->_queue; }

  template <typename... Args>
  static std::shared_ptr<Derived> Create(Args &&...args) {
    std::shared_ptr<Derived> r{new Derived{std::forward<Args>(args)...}};
    r->OnCreated();
    return r;
  }

  std::shared_ptr<Derived> Self() {
    return std::static_pointer_cast<Derived>(this->shared_from_this());
  }

protected:
  virtual void OnSubscribed(std::shared_ptr<Observer>) {}

  virtual void OnCreated() {}

  void RemoveSubscription(std::shared_ptr<Observer> ptr) {
    if (auto it = std::find_if(this->_observers.begin(), this->_observers.end(),
                               [&](auto v) { return v.lock() == ptr; });
        it != this->_observers.end()) {
      this->_observers.erase(it);
    }
  }

protected:
  template <typename T> void Notify(T &&value) const {
    std::for_each(this->_observers.begin(), this->_observers.end(),
                  [&](auto o) {
                    if (auto observer = o.lock(); observer) {
                      observer->Execute(value);
                    }
                  });
  }

protected:
  std::shared_ptr<AsyncQueue> _queue;

private:
  std::vector<std::weak_ptr<Observer>> _observers;
};