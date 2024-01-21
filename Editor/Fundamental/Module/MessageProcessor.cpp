#pragma once

#include "MessageProcessor.h"
#include "AsyncQueue.h"

namespace Vandrouka::Fundamental::Private {

void AggregatedProcessor::Process(Ref<IReferenced> state, Ref<IMessage> msg,
                                  Ref<IMessageOutput> sink) {

  ExecuteAsync([state, msg, sink, this]() {
    auto [start, end] = this->_processors.equal_range(msg->GetTypeID());

    if (start == end) {
      if (_unhandled) {
        _unhandled->Process(state, msg, sink);
        return;
      } else {
        assert(false && "Unhandled message");
      }
    }

    while (start != end) {
      (*start).second->Process(state, msg, sink);
      ++start;
    }
  });
}

void AggregatedProcessor::AddProcessor(Ref<IMessageProcessor> processor) {
  for (auto id : processor->GetMessageIds()) {
    this->_ids.push_back(id);
    this->_processors.insert(std::make_pair(id, processor));
  }
}

void AggregatedProcessor::SetUnhandledProcessor(
    Ref<IMessageProcessor> processor) {
  _unhandled = processor;
}

void AggregatedProcessorAsync::ExecuteAsync(std::function<void()> cb) {
  this->_queue->Enqueue(new CallbackTask{cb});
}

} // namespace Vandrouka::Fundamental::Private