#pragma once

#include <Fundamental/Interface/IAsyncTask.h>
#include <Fundamental/Interface/IMessage.h>
#include <vsg/all.h>

namespace Vandrouka::State::Messages {

class ICompileMessage : public IMessage {
public:
  virtual vsg::ref_ptr<vsg::Node> GetResultObject() = 0;
  virtual Ref<IAsyncTask> GetCompletion() = 0;
  // std::function<void(vsg::ref_ptr<vsg::Node>, vsg::CompileResult &)>
  //     OnComplete;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ICompileMessage, 0xb1, 0x8c, 0x43, 0x13,
            0xe6, 0xdb, 0x47, 0x5, 0x8f, 0x2a, 0x6f, 0x6e, 0x6f, 0x85, 0x7e,
            0x94);
