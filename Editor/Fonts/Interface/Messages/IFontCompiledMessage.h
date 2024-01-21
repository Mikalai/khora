#pragma once

#include <Fundamental/Interface/IMessage.h>
#include <vsg/text/Font.h>

namespace Vandrouka::Fonts::Messages {

class IFontCompiledMessage : public IMessage {
public:
  virtual const std::string &GetDisplayName() const = 0;
  virtual vsg::ref_ptr<vsg::Font> GetFont() const = 0;
  virtual vsg::ref_ptr<vsg::Node> GetRoot() const = 0;
  virtual Ref<IReferenced> GetState() const = 0;
};

} // namespace Vandrouka::Fonts::Messages

DECLARE_IID(Vandrouka::Fonts::Messages::IFontCompiledMessage, 0x19, 0x90, 0x20,
            0x67, 0xd1, 0x23, 0x40, 0x28, 0x96, 0x66, 0x49, 0xcd, 0xa4, 0x5c,
            0xe9, 0x1c);
