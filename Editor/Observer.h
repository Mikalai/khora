#pragma once

#include <boost/asio/io_context.hpp>
#include <memory>
#include <vector>
#include <functional>
#include "AsyncQueue.h"

class Subscription : public std::enable_shared_from_this<Subscription> {
public:

    Subscription(std::function<void()> onDelete)
    : _onDelete{onDelete}{

    }

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

template<typename Derived, typename Observer, typename Interface>
class Observable : public Interface, public std::enable_shared_from_this<Observable<Derived, Observer, Interface>> {
public:

    Observable(boost::asio::io_context& ctx) {
        (this->_queue = std::make_shared<AsyncQueue>(ctx))->Start();
    }

    [[nodiscard]]
    SubscriptionPtr Subscribe(std::shared_ptr<Observer> observer) override {
        this->_queue->Enqueue([&]() {
            this->_observers.push_back(observer);
            this->OnSubscribed(observer);
            });

        return std::make_shared<Subscription>([this, observer]() {
            this->_queue->Enqueue([this, observer]() {
                this->RemoveSubscription(observer);
            });
        });
    }

    std::shared_ptr<AsyncQueue> GetSyncContext() override{
        return this->_queue;
    }

    static std::shared_ptr<Derived> Create(boost::asio::io_context& ctx) {
        std::shared_ptr<Derived> r{ new Derived{ctx} };
        r->OnCreated();
        return r;
    }

    std::shared_ptr<Derived> Self() {
        return std::static_pointer_cast<Derived>(this->shared_from_this());
    }

protected:

    virtual void OnSubscribed(std::shared_ptr<Observer>) {

    }

    virtual void OnCreated() {

    }

    void RemoveSubscription(std::shared_ptr<Observer> ptr) {
        if (auto it = std::find_if(this->_observers.begin(), this->_observers.end(), [&](auto v) {
            return v.lock() == ptr;
            }); it != this->_observers.end()) {
            this->_observers.erase(it);
        }
    }

protected:

    template<typename T>
    void Notify(T&& value) {
        std::for_each(this->_observers.begin(), this->_observers.end(), [&](auto o) {
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