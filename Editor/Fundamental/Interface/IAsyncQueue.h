#pragma once

#include <boost/asio/io_context.hpp>
#include <Fundamental/Interface/IAsyncTask.h>
#include <string>

namespace Vandrouka {
namespace Fundamental {

class IAsyncQueue : public Fundamental::IReferenced {
public:
  virtual void Enqueue(Ref<IAsyncTask> task) = 0;
  virtual void Complete() = 0;

  virtual void Execute(Ref<IAsyncTask> task) = 0;
  virtual boost::asio::io_context &GetIoContext() = 0;
};

} // namespace Fundamental

using Fundamental::IAsyncQueue;

} // namespace Vandrouka

DECLARE_IID(Vandrouka::Fundamental::IAsyncQueue, 0xbd, 0xf5, 0xc1, 0x5c, 0xcd,
            0xb3, 0x48, 0xbc, 0xbb, 0x3a, 0x4c, 0xa4, 0xbb, 0x91, 0xb8, 0x69);

DECLARE_CID(Fundamental, AsyncQueue, 0x60, 0xae, 0xc3, 0x8c, 0xf7, 0x72, 0x4f,
            0x1, 0x9e, 0xb1, 0xb2, 0x17, 0xb3, 0xae, 0x50, 0xe9);