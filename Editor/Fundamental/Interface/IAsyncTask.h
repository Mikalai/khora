#pragma once

#include <Fundamental/Interface/IReferenced.h>
#include <string>

namespace Vandrouka {
namespace Fundamental {

class IAsyncTask : public Fundamental::IReferenced {
public:
  virtual void Execute() = 0;
};

} // namespace Fundamental

using Fundamental::IAsyncTask;

} // namespace Vandrouka

DECLARE_IID(Vandrouka::Fundamental::IAsyncTask, 0x3c, 0xc3, 0x5a, 0x99, 0xd0,
            0xa7, 0x4c, 0xfb, 0x91, 0x53, 0x6f, 0x5f, 0x29, 0xcd, 0xdb, 0x3a);