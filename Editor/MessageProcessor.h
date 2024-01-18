#pragma once

#include "IObserver.h"
#include "IAsyncQueue.h"

namespace Vandrouka {

class AggregatedProcessor
    : public ReferenceCountedBase<AggregatedProcessor, IAggregatedProcessor> {

public:
  using Interfaces = QueryInterfaces<AggregatedProcessor, IAggregatedProcessor,
                                     IMessageProcessor, IReferenced>;

  std::span<MessageId> GetMessageIds() override { return _ids; }
  void Process(Ref<IReferenced> state, Ref<IMessage> msg,
               Ref<IMessageOutput> sink) override;
  void AddProcessor(Ref<IMessageProcessor> processor) override;
  void SetUnhandledProcessor(Ref<IMessageProcessor> processor) override;

protected:

  virtual void ExecuteAsync(std::function<void()> cb) = 0;

private:
  std::vector<MessageId> _ids;
  std::unordered_multimap<MessageId, Ref<IMessageProcessor>> _processors;
  Ref<IMessageProcessor> _unhandled;

};

class AggregatedProcessorAsync : public AggregatedProcessor {
public:

  AggregatedProcessorAsync(Ref<IAsyncQueue> queue) : _queue{queue} {}
  
protected:
  void ExecuteAsync(std::function<void()> cb) override;

private:
  Ref<IAsyncQueue> _queue;
};


template <ReferenceCounted Derived, ReferenceCounted State,
          typename... Messages>
class MessageProcessorBase
    : public ReferenceCountedBase<Derived, IMessageProcessor> {

  template <typename... Msg> struct Invoke;

  template <typename Msg, typename... O> struct Invoke<Msg, O...> {

    static std::vector<MessageId> GetMessageIds() {
      std::vector<MessageId> result;
      result.push_back(GetIID<Msg>::Id);
      auto other = Invoke<O...>::GetMessageIds();
      result.insert(result.end(), other.begin(), other.end());
      return result;
    }

    static void Process(Derived *self, Ref<State> state, Ref<IMessage> message,
                        Ref<IMessageOutput> sink) {
      if (auto msg = message.Cast<Msg>(); msg) {
        self->ProcessMessage(state, msg, sink);
      } else {
        Invoke<O...>::Process(self, state, message, sink);
      }
    }
  };

  template <> struct Invoke<> {
    static std::vector<MessageId> GetMessageIds() { return {}; }
    static void Process(Derived *self, Ref<State> state, Ref<IMessage> message,
                        Ref<IMessageOutput> sink) {}
  };

public:
  std::span<MessageId> GetMessageIds() override {
    static std::vector<MessageId> ids = Invoke<Messages...>::GetMessageIds();
    return ids;
  }

  void Process(Ref<IReferenced> state, Ref<IMessage> msg,
               Ref<IMessageOutput> sink) override {
    if (auto s = state.Cast<State>(); s) {
      Invoke<Messages...>::Process(static_cast<Derived *>(this), s, msg, sink);
    }
  }
};

} // namespace Vandrouka
