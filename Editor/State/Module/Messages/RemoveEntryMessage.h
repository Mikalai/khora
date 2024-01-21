#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IRemoveEntryMessage.h>

namespace Vandrouka::State::Private::Messages {

class RemoveEntryMessage
    : public Fundamental::Private::MessageBase<RemoveEntryMessage, State::Messages::IRemoveEntryMessage> {
public:
  RemoveEntryMessage(Catalog::EntryPath path) : _path{path} {}

  Catalog::EntryPath GetPath() const override { return _path; }

private:
  Catalog::EntryPath _path;
};

} // namespace Vandrouka