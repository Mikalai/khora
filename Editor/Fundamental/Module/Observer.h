#pragma once

#include <boost/asio/io_context.hpp>
#include <functional>
#include <memory>
#include <vector>
#include <Fundamental/Interface/IObserver.h>
#include <Fundamental/Interface/IMessageOutput.h>
#include <Fundamental/Module/AsyncQueue.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::Fundamental::Private {

template <typename Derived, typename... I>
class ObservableBase : public ReferenceCountedBase<Derived, I..., IObservable> {

  using Base = ReferenceCountedBase<Derived, I..., IObservable>;
  using SelfType = ObservableBase<Derived, I...>;

  /*class SubscribedMessage
      : public Fundamental::Private::MessageBase<SubscribedMessage, ISubscribedMessage> {
  public:
    SubscribedMessage(Ref<IReferenced> observable) : _observable{observable} {}

    Ref<IReferenced> GetObservable() override { return _observable; }

  private:
    Ref<IReferenced> _observable;
  };*/

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
    this->_queue = Create<Instances::Fundamental::AsyncQueue, IAsyncQueue>();
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
