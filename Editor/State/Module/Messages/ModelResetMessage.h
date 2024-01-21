#pragma once

#include <State/Interface/Messages/IModelResetMessage.h>
#include <Fundamental/Module/MessageBase.h>

namespace Vandrouka::State::Private::Messages {

class ModelResetMessage
    : public Fundamental::Private::MessageBase<ModelResetMessage, State::Messages::IModelResetMessage> {
public:
  ModelResetMessage(Ref<Catalog::IEntry> root) : _root{root} {}

  Ref<Catalog::IEntry> GetRoot() const { return _root; }

private:
  Ref<Catalog::IEntry> _root;
};

} // namespace Vandrouka