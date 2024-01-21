#pragma once

#include <vsg/all.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class ISceneCompeledMessage : public IMessage {
public:
  virtual vsg::ref_ptr<vsg::Node> GetRoot() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::ISceneCompeledMessage, 0xa2, 0xd4, 0xa1,
            0x7, 0x95, 0xbe, 0x41, 0x34, 0xb3, 0x79, 0x7b, 0x77, 0x62, 0xef,
            0xeb, 0xd9);
