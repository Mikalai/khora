#pragma once

#include <Fundamental/Interface/IError.h>
#include <Fundamental/Interface/IMessage.h>
#include <Fundamental/Interface/IReferenced.h>
#include <boost/uuid/uuid_hash.hpp>
#include <span>

namespace Vandrouka {

namespace Fundamental {

class IMessageOutput : public Fundamental::IReferenced {
public:
  virtual void SubmitMessage(Ref<IMessage> msg) = 0;
  virtual void SubmitError(Ref<IError> msg) = 0;

  void SubmitAllMessages(auto container) {
    for (auto it = std::begin(container); it != std::end(container); ++it) {
      SubmitMessage(*it);
    }
  }
};

} // namespace Fundamental

using Fundamental::IMessageOutput;

} // namespace Vandrouka

DECLARE_IID(::Vandrouka::Fundamental::IMessageOutput, 0x63, 0x3e, 0x6c, 0x85,
            0xe1, 0xda, 0x41, 0x74, 0x93, 0xcf, 0x4c, 0x14, 0xf7, 0x21, 0xb2,
            0x3);
