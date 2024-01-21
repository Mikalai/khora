#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ISceneCompeledMessage.h>

namespace Vandrouka::State::Private::Messages {

class SceneCompeledMessage
    : public Fundamental::Private::MessageBase<SceneCompeledMessage,
                                               State::Messages::ISceneCompeledMessage> {
public:
  SceneCompeledMessage(vsg::ref_ptr<vsg::Node> root) : _root{root} {}
  vsg::ref_ptr<vsg::Node> GetRoot() const override { return _root; }

private:
  vsg::ref_ptr<vsg::Node> _root;
};

} // namespace Vandrouka::State::Private::Messages
