#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class RefreshFontsMessage
    : public MessageBase<RefreshFontsMessage, IRefreshFontsMessage> {
public:
  RefreshFontsMessage(bool force) : _force{force} {}
  bool GetForce() const override { return _force; }

private:
  bool _force;
};

} // namespace Vandrouka