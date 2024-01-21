#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ISelectEntryMessage.h>

namespace Vandrouka::State::Private::Messages {

class SelectEntryMessage
    : public Fundamental::Private::MessageBase<SelectEntryMessage, State::Messages::ISelectEntryMessage> {
public:
  SelectEntryMessage(Catalog::EntryPath path) : _path{path} {}

  Catalog::EntryPath GetPath() const override { return _path; }

private:
  Catalog::EntryPath _path;
};

} // namespace Vandrouka