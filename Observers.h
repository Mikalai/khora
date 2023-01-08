#pragma once

#include <vector>

template<typename T>
class Observer {
public:
    virtual void Next(T& msg) {

    }

    virtual void Complete() {

    }
};


template<typename T>
class Observable {
public:

    virtual void Subscribe(Observer<T>* observer) {
        _observers.push_back(observer);
    }

    virtual void Notify(T& msg) {
        for (auto& v : _observers) {
            v->Next(msg);
        }
    }

private:
    std::vector<Observer<T>*> _observers;
};
