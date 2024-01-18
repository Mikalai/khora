#include "AsyncQueue.h"
#include "IAsyncQueue.h"
#include "IoContext.h"
#include <concepts>

namespace Vandrouka {

class LockTask : public ReferenceCountedBase<LockTask, IAsyncTask> {
public:
  using Interfaces = QueryInterfaces<LockTask, IAsyncTask, IReferenced>;

  LockTask(std::binary_semaphore &s, Ref<IAsyncTask> task)
      : _s{s}, _task{task} {}

  virtual ~LockTask() {}

  // bool QueryInterface(const InterfaceId &id, void **o) override {
  //   if (id == GetIID<IAsyncTask>::Id) {
  //     *o = static_cast<IAsyncTask *>(this);
  //   } else if (id == GetIID<IReferenced>::Id) {
  //     *o = static_cast<IReferenced *>(this);
  //   } else {
  //     *o = nullptr;
  //   }

  //   if (*o) {
  //     this->AddRef();
  //   }

  //   return *o != nullptr;
  // }

  void Execute() override {
    _task->Execute();
    _s.release();
  }

private:
  std::binary_semaphore &_s;
  Ref<IAsyncTask> _task;
};

class AsyncQueue final : public ReferenceCountedBase<AsyncQueue, IAsyncQueue> {
public:
  using Interfaces = QueryInterfaces<AsyncQueue, IAsyncQueue, IReferenced>;

  AsyncQueue(std::shared_ptr<boost::asio::io_context> ctx)
      : _ctx{ctx}, _timer{*ctx} {
    Start();
  }

  virtual ~AsyncQueue() {}

  /*bool QueryInterface(const InterfaceId &id, void **o) override {
    if (id == GetIID<IAsyncQueue>::Id) {
      *o = static_cast<IAsyncQueue *>(this);
    } else if (id == GetIID<IReferenced>::Id) {
      *o = static_cast<IReferenced *>(this);
    } else {
      *o = nullptr;
    }

    if (*o) {
      this->AddRef();
    }

    return *o != nullptr;
  }*/

  void Start() {
    _timer.expires_from_now(boost::posix_time::seconds(60));
    _timer.async_wait(
        boost::bind(&AsyncQueue::Process, Self(), boost::placeholders::_1));
  }

  void Process(boost::system::error_code) {
    Ref<IAsyncTask> task;
    while (true) {
      {
        std::unique_lock lock{_cs};

        if (_complete)
          return;

        _currentThread = std::this_thread::get_id();
        if (!_tasks.empty()) {
          task = _tasks.front();
          _tasks.pop();
        } else {
          _timer.expires_from_now(boost::posix_time::seconds(60));
          _timer.async_wait(boost::bind(&AsyncQueue::Process, Self(),
                                        boost::placeholders::_1));
          _currentThread = {};
          return;
        }
      }

      if (task) {
        task->Execute();
      }
    }
  }

  void Enqueue(Ref<IAsyncTask> task) override {
    std::unique_lock lock{_cs};
    if (_currentThread == std::this_thread::get_id()) {
      task->Execute();
    } else {
      _tasks.push(task);
      _timer.cancel();
    }
  }

  void Complete() override {
    std::unique_lock lock{_cs};
    _complete = true;
    _timer.cancel();
  }

  void Execute(Ref<IAsyncTask> task) override {
    std::binary_semaphore s{0};
    static_assert(std::is_convertible_v<LockTask *, IAsyncTask *>,
                  "LockTask is not derived from IAsyncTask");

    Ref<IAsyncTask> wrappedTask{new LockTask(s, task)};

    Enqueue(wrappedTask);

    s.acquire();
  }

  boost::asio::io_context &GetIoContext() override { return *_ctx; }

private:
  std::shared_ptr<boost::asio::io_context> _ctx;
  boost::asio::deadline_timer _timer;
  std::mutex _cs;
  bool _complete{false};
  std::queue<Ref<IAsyncTask>> _tasks;
  std::thread::id _currentThread;
};

IReferenced *CreateAsyncQueue() {
  // static_assert(std::derived_from<::Vandrouka::AsyncQueue, IReferenced>,
  // "AsyncQueue is not IReferenced");
  return (IAsyncQueue *)(new AsyncQueue(GetIoContext()));
}

} // namespace Vandrouka

void AsyncQueue::Start() {
  _timer.expires_from_now(boost::posix_time::seconds(60));
  _timer.async_wait(boost::bind(&AsyncQueue::Process, shared_from_this(),
                                boost::placeholders::_1));
}

void AsyncQueue::Enqueue(Task task) {
  std::unique_lock lock{_cs};
  if (_currentThread == std::this_thread::get_id()) {
    task();
  } else {
    _tasks.push(task);
    _timer.cancel();
  }
}

void AsyncQueue::Complete() {
  std::unique_lock lock{_cs};
  _complete = true;
  _timer.cancel();
}

void AsyncQueue::Process(boost::system::error_code) {
  Task task;
  while (true) {
    {
      std::unique_lock lock{_cs};

      if (_complete)
        return;

      _currentThread = std::this_thread::get_id();
      if (!_tasks.empty()) {
        task = _tasks.front();
        _tasks.pop();
      } else {
        _timer.expires_from_now(boost::posix_time::seconds(60));
        _timer.async_wait(boost::bind(&AsyncQueue::Process, shared_from_this(),
                                      boost::placeholders::_1));
        _currentThread = {};
        return;
      }
    }

    if (task) {
      task();
    }
  }
}
