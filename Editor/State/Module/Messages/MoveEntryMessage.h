#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IMoveEntryMessage.h>

namespace Vandrouka::State::Private::Messages {

class MoveEntryMessage
    : public Fundamental::Private::MessageBase<
          MoveEntryMessage, State::Messages::IMoveEntryMessage> {
public:
  MoveEntryMessage(Catalog::EntryPath src, Catalog::EntryPath dst)
      : _src{src}, _dst{dst} {}
  Catalog::EntryPath GetSourcePath() const override { return _src; }
  Catalog::EntryPath GetTargetPath() const override { return _dst; }

private:
  Catalog::EntryPath _src;
  Catalog::EntryPath _dst;
};

} // namespace Vandrouka::State::Private::Messages