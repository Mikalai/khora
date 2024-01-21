#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <Fonts/Interface/Messages/ICompileFontMessage.h>

namespace Vandrouka::Fonts::Private::Messages {

class CompileFontMessage
    : public Fundamental::Private::MessageBase<CompileFontMessage, Fonts::Messages::ICompileFontMessage> {
public:
  CompileFontMessage(std::string name, Ref<IReferenced> state)
      : _name{name}, _state{state} {}

  const std::string &GetDisplayName() const override { return _name; }
  Ref<IReferenced> GetState() const override { return _state; }

private:
  std::string _name;
  Ref<IReferenced> _state;
};


} // namespace Vandrouka