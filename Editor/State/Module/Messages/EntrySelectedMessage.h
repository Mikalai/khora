#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IEntrySelectedMessage.h>

namespace Vandrouka::State::Private::Messages {

class EntrySelectedMessage
    : public Fundamental::Private::MessageBase<
          EntrySelectedMessage, State::Messages::IEntrySelectedMessage> {
public:
  EntrySelectedMessage(Catalog::EntryRef entry) : _entry{entry} {}

  Catalog::EntryRef GetSelectedEntry() override { return _entry; }

private:
  Catalog::EntryRef _entry;
};

} // namespace Vandrouka::State::Private::Messages