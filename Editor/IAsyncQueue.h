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

#include "IReferenced.h"

namespace Vandrouka {

class ICustomState : public IReferenced {
public:
  virtual std::string GetName() = 0;
};

template <> struct GetIID<ICustomState> {
  static constexpr InterfaceId Id = {{0x1f, 0xde, 0x77, 0xca, 0x8e, 0xb5, 0x44,
                                      0xf7, 0xbe, 0x51, 0xcb, 0xb4, 0x6b, 0x1,
                                      0x83, 0x5}};
};

class IAsyncTask : public IReferenced {
public:
  virtual void Execute() = 0;
};

template <> struct GetIID<IAsyncTask> {
  static constexpr InterfaceId Id = {{0x3c, 0xc3, 0x5a, 0x99, 0xd0, 0xa7, 0x4c,
                                      0xfb, 0x91, 0x53, 0x6f, 0x5f, 0x29, 0xcd,
                                      0xdb, 0x3a}};
};

class IAsyncQueue : public IReferenced {
public:
  virtual void Enqueue(Ref<IAsyncTask> task) = 0;
  virtual void Complete() = 0;

  virtual void Execute(Ref<IAsyncTask> task) = 0;
  virtual boost::asio::io_context &GetIoContext() = 0;
};

template <> struct GetIID<IAsyncQueue> {
  static constexpr InterfaceId Id = {{0xbd, 0xf5, 0xc1, 0x5c, 0xcd, 0xb3, 0x48,
                                      0xbc, 0xbb, 0x3a, 0x4c, 0xa4, 0xbb, 0x91,
                                      0xb8, 0x69}};
};

class AsyncQueue;

template <> struct GetCID<AsyncQueue> {
  static constexpr ClassId Id = {{0x60, 0xae, 0xc3, 0x8c, 0xf7, 0x72, 0x4f, 0x1,
                                  0x9e, 0xb1, 0xb2, 0x17, 0xb3, 0xae, 0x50,
                                  0xe9}};
};

} // namespace Vandrouka
