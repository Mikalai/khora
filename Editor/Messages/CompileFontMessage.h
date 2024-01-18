#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../ISystemFonts.h"
#include "../Observer.h"

namespace Vandrouka {

class CompileFontMessage
    : public MessageBase<CompileFontMessage, ICompileFontMessage> {
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