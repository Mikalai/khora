#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <Fonts/Module/ISystemFontsPrivate.h>
#include <Fonts/Interface/Messages/IFontCompiledMessage.h>

namespace Vandrouka::Fonts::Private::Messages {

class FontCompiledMessage
    : public Fundamental::Private::MessageBase<FontCompiledMessage, Fonts::Messages::IFontCompiledMessage> {
public:
  FontCompiledMessage(std::string name, vsg::ref_ptr<vsg::Font> font,
                      vsg::ref_ptr<vsg::Node> node, Ref<IReferenced> state)
      : _name{name}, _font{font}, _node{node}, _state{state} {}

  const std::string &GetDisplayName() const override { return _name; }
  vsg::ref_ptr<vsg::Font> GetFont() const override { return _font; }
  vsg::ref_ptr<vsg::Node> GetRoot() const override { return _node; }
  Ref<IReferenced> GetState() const override { return _state; }

private:
  std::string _name;
  vsg::ref_ptr<vsg::Font> _font;
  vsg::ref_ptr<vsg::Node> _node;
  Ref<IReferenced> _state;
};


} // namespace Vandrouka
