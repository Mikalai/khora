#pragma once

#include <queue>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind/bind.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

class AsyncQueue : public std::enable_shared_from_this<AsyncQueue> {
public:
    AsyncQueue(boost::asio::io_context& ctx)
        : _ctx{ctx}
        , _timer{ctx}
    {
    }

    void Start();

    using Task = std::function<void()>;

    void Enqueue(Task task);

private:

    void Process(boost::system::error_code ec);

private:
    boost::asio::io_context& _ctx;
    boost::asio::deadline_timer _timer;
    std::mutex _cs;
    std::queue<Task> _tasks;
};
