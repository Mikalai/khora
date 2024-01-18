#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class ModelResetMessage
    : public MessageBase<ModelResetMessage, IModelResetMessage> {
public:
  ModelResetMessage(Ref<IEntry> root) : _root{root} {}

  Ref<IEntry> GetRoot() const { return _root; }

private:
  Ref<IEntry> _root;
};


} // namespace Vandrouka