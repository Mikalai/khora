#include "AsyncQueue.h"

void AsyncQueue::Start() {
    _timer.expires_from_now(boost::posix_time::seconds(60));
    _timer.async_wait(boost::bind(&AsyncQueue::Process, shared_from_this(), boost::placeholders::_1));
}

void AsyncQueue::Enqueue(Task task) {
    std::unique_lock lock{ _cs };
    _tasks.push(task);
    _timer.cancel();
}

void AsyncQueue::Process(boost::system::error_code ec) {
    Task task;
    while (true)
    {
        {
            std::unique_lock lock{ _cs };
            if (!_tasks.empty()) {
                task = _tasks.front();
                _tasks.pop();
            }
            else {
                _timer.expires_from_now(boost::posix_time::seconds(60));
                _timer.async_wait(boost::bind(&AsyncQueue::Process, shared_from_this(), boost::placeholders::_1));
                return;
            }
        }

        if (task) {
            task();
        }
    }
}
