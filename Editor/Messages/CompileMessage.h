#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class CompileMessage : public MessageBase<CompileMessage, ICompileMessage> {
public:
  CompileMessage(vsg::ref_ptr<vsg::Node> _node, Ref<IAsyncTask> _completion)
      : _node(_node), _completion(_completion) {}

  vsg::ref_ptr<vsg::Node> GetResultObject() override { return _node; }

  Ref<IAsyncTask> GetCompletion() override { return _completion; }

private:
  vsg::ref_ptr<vsg::Node> _node;
  Ref<IAsyncTask> _completion;
};

} // namespace Vandrouka