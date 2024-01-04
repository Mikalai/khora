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
class MessageBase : public ReferenceCountedBase<Derived, Interface> {
public:
  bool QueryInterface(const InterfaceId &id, void **o) override {
    if (id == GetIID<Interface>::Id) {
      *o = static_cast<Interface *>(this);
    } else if (id == GetIID<IMessage>::Id) {
      *o = static_cast<IMessage *>(this);
    } else if (id == GetIID<IReferenced>::Id) {
      *o = static_cast<IReferenced *>(this);
    } else {
      *o = nullptr;
    }

    if (*o) {
      this->AddRef();
    }

    return *o != nullptr;
  }
};

template <typename Derived, typename Base>
class ObservableBase2 : public Base, public IObservable {

  using SelfType = ObservableBase2<Derived, Base>;

  class SubscribedMessage
      : public ReferenceCountedBase<SubscribedMessage, ISubscribedMessage> {
  public:
    SubscribedMessage(Ref<IReferenced> observable) : _observable{observable} {}

    bool QueryInterface(const InterfaceId &id, void **o) override {
      if (id == GetIID<ISubscribedMessage>::Id) {
        *o = static_cast<ISubscribedMessage *>(this);
      } else if (id == GetIID<IMessage>::Id) {
        *o = static_cast<IMessage *>(this);
      } else if (id == GetIID<IReferenced>::Id) {
        *o = static_cast<IReferenced *>(this);
      } else {
        *o = nullptr;
      }

      if (*o) {
        this->AddRef();
      }

      return *o != nullptr;
    }

    Ref<IReferenced> GetObservable() override { return _observable; }

  private:
    Ref<IReferenced> _observable;
  };

  class CallbackTask : public ReferenceCountedBase<CallbackTask, IAsyncTask> {
  public:
    CallbackTask(std::function<void()> callback) : _callback{callback} {}

    virtual ~CallbackTask() {}

    bool QueryInterface(const InterfaceId &id, void **o) override {
      if (id == GetIID<IAsyncTask>::Id) {
        *o = static_cast<IAsyncTask *>(this);
      } else if (id == GetIID<IReferenced>::Id) {
        *o = static_cast<IReferenced *>(this);
      } else {
        *o = nullptr;
      }

      if (*o) {
        this->AddRef();
      }

      return *o != nullptr;
    }

    void Execute() override { this->_callback(); }

  private:
    std::function<void()> _callback;
  };

  class Subscription : public ReferenceCountedBase<Subscription, IReferenced> {
  public:
    Subscription(Ref<Derived> self, Ref<IObserver> observer)
        : _self{self}, _observer{observer} {}

    virtual ~Subscription() { _self->Unsubscribe(_observer); }

    bool QueryInterface(const InterfaceId &id, void **o) override {
      if (id == GetIID<IReferenced>::Id) {
        *o = static_cast<IReferenced *>(this);
      } else {
        *o = nullptr;
      }

      if (*o) {
        this->AddRef();
      }

      return *o != nullptr;
    }

  private:
    Ref<Derived> _self;
    Ref<IObserver> _observer;
  };

  friend class Subscription;

protected:
  ObservableBase2() {
    this->_queue = Create<AsyncQueue, IAsyncQueue>();
    assert(this->_queue);
  }

  void ExecuteAsync(std::function<void()> cb) {
    this->_queue->Enqueue(new CallbackTask{cb});
  }

public:
  bool QueryInterface(const InterfaceId &id, void **o) override {
    if (Base::QueryInterface(id, o)) {
      return true;
    }

    if (id == GetIID<IObservable>::Id) {
      *o = static_cast<IObservable *>(this);
    } else {
      *o = nullptr;
    }

    if (*o) {
      this->AddRef();
    }

    return *o != nullptr;
  }

  Ref<IReferenced> Subscribe(Ref<IObserver> value) override {
    Ref<IAsyncTask> subscriptionTask{new CallbackTask{[this, value]() mutable {
      this->_observers.push_back(value);
      value->OnNext(new SubscribedMessage{this->Self()});
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
  void OnMessage(Ref<IMessage> value) const {
    std::for_each(this->_observers.begin(), this->_observers.end(),
                  [&](auto o) { o->OnNext(value); });
  }

  void OnError(Ref<IError> value) const {
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

template <typename Derived, typename... Interfaces>
class ObservableBase : public ReferenceCountedBase<Derived, Interfaces...> {

  using Base = ReferenceCountedBase<Derived, Interfaces...>;
  using SelfType = ObservableBase<Derived, Interfaces...>;

  class SubscribedMessage
      : public ReferenceCountedBase<SubscribedMessage, ISubscribedMessage> {
  public:
    SubscribedMessage(Ref<IReferenced> observable) : _observable{observable} {}

    bool QueryInterface(const InterfaceId &id, void **o) override {
      if (id == GetIID<ISubscribedMessage>::Id) {
        *o = static_cast<ISubscribedMessage *>(this);
      } else if (id == GetIID<IMessage>::Id) {
        *o = static_cast<IMessage *>(this);
      } else if (id == GetIID<IReferenced>::Id) {
        *o = static_cast<IReferenced *>(this);
      } else {
        *o = nullptr;
      }

      if (*o) {
        this->AddRef();
      }

      return *o != nullptr;
    }

    Ref<IReferenced> GetObservable() override { return _observable; }

  private:
    Ref<IReferenced> _observable;
  };

  class CallbackTask : public ReferenceCountedBase<CallbackTask, IAsyncTask> {
  public:
    CallbackTask(std::function<void()> callback) : _callback{callback} {}

    virtual ~CallbackTask() {}

    bool QueryInterface(const InterfaceId &id, void **o) override {
      if (id == GetIID<IAsyncTask>::Id) {
        *o = static_cast<IAsyncTask *>(this);
      } else if (id == GetIID<IReferenced>::Id) {
        *o = static_cast<IReferenced *>(this);
      } else {
        *o = nullptr;
      }

      if (*o) {
        this->AddRef();
      }

      return *o != nullptr;
    }

    void Execute() override { this->_callback(); }

  private:
    std::function<void()> _callback;
  };

  class Subscription : public ReferenceCountedBase<Subscription, IReferenced> {
  public:
    Subscription(Ref<Derived> self, Ref<IObserver> observer)
        : _self{self}, _observer{observer} {}

    virtual ~Subscription() { _self->Unsubscribe(_observer); }

    bool QueryInterface(const InterfaceId &id, void **o) override {
      if (id == GetIID<IReferenced>::Id) {
        *o = static_cast<IReferenced *>(this);
      } else {
        *o = nullptr;
      }

      if (*o) {
        this->AddRef();
      }

      return *o != nullptr;
    }

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
    Ref<IAsyncTask> subscriptionTask{new CallbackTask{[this, value]() mutable {
      this->_observers.push_back(value);
      value->OnNext(new SubscribedMessage{this->Self()});
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
  void OnMessage(Ref<IMessage> value) const {
    std::for_each(this->_observers.begin(), this->_observers.end(),
                  [&](auto o) { o->OnNext(value); });
  }

  void OnError(Ref<IError> value) const {
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