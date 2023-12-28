#pragma once

#include <semaphore>
#include <thread>
#include <queue>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind/bind.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

class CustomState : public std::enable_shared_from_this<CustomState> {
public:
    virtual std::string GetName() { return ""; }
};

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

    auto Execute(auto func) {
        std::binary_semaphore s{ 0 };

        if constexpr (std::is_same_v<void, decltype(func())>) {
            Enqueue([&]() {
                func();
                s.release();
                });

            s.acquire();
        }
        else {
            decltype(func()) result{};
            Enqueue([&]() {
                result = func();
                s.release();
            });
            s.acquire();
            return result;
        }
    }

private:

    void Process(boost::system::error_code ec);

private:
    boost::asio::io_context& _ctx;
    boost::asio::deadline_timer _timer;
    std::mutex _cs;
    std::queue<Task> _tasks;
    std::thread::id _currentThread;
};
