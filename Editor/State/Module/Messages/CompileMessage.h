#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ICompileMessage.h>

namespace Vandrouka::State::Private::Messages {

class CompileMessage : public Fundamental::Private::MessageBase<
                           CompileMessage, State::Messages::ICompileMessage> {
public:
  CompileMessage(vsg::ref_ptr<vsg::Node> _node, Ref<IAsyncTask> _completion)
      : _node(_node), _completion(_completion) {}

  vsg::ref_ptr<vsg::Node> GetResultObject() override { return _node; }

  Ref<IAsyncTask> GetCompletion() override { return _completion; }

private:
  vsg::ref_ptr<vsg::Node> _node;
  Ref<IAsyncTask> _completion;
};

} // namespace Vandrouka::State::Private::Messages