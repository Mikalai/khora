#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class SceneCompeledMessage
    : public MessageBase<SceneCompeledMessage, ISceneCompeledMessage> {
public:
  SceneCompeledMessage(vsg::ref_ptr<vsg::Node> root) : _root{root} {}
  vsg::ref_ptr<vsg::Node> GetRoot() const override { return _root; }

private:
  vsg::ref_ptr<vsg::Node> _root;
};


} // namespace Vandrouka