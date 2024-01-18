#pragma once

#include <algorithm>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/bind/bind.hpp>
#include <memory>
#include <queue>
#include <semaphore>
#include <string>
#include <thread>
#include <vector>
#include "IAsyncQueue.h"
#include "Referenced.h"

namespace Vandrouka {

class CallbackTask : public ReferenceCountedBase<CallbackTask, IAsyncTask> {
public:
  CallbackTask(std::function<void()> callback) : _callback{callback} {}

  virtual ~CallbackTask() {}

  void Execute() override { this->_callback(); }

private:
  std::function<void()> _callback;
};

}

class CustomState : public std::enable_shared_from_this<CustomState> {
public:
  virtual std::string GetName() { return ""; }
};

class AsyncQueue : public std::enable_shared_from_this<AsyncQueue> {
public:
  AsyncQueue(std::shared_ptr<boost::asio::io_context> ctx)
      : _ctx{ctx}, _timer{*ctx} {}

  void Start();

  using Task = std::function<void()>;

  void Enqueue(Task task);

  void Complete();

  auto Execute(auto func) {
    std::binary_semaphore s{0};

    if constexpr (std::is_same_v<void, decltype(func())>) {
      Enqueue([&]() {
        func();
        s.release();
      });

      s.acquire();
    } else {
      decltype(func()) result{};
      Enqueue([&]() {
        result = func();
        s.release();
      });
      s.acquire();
      return result;
    }
  }

  auto &GetIoContext() { return *_ctx; }

private:
  void Process(boost::system::error_code ec);

private:
  std::shared_ptr<boost::asio::io_context> _ctx;
  boost::asio::deadline_timer _timer;
  std::mutex _cs;
  bool _complete{false};
  std::queue<Task> _tasks;
  std::thread::id _currentThread;
};
