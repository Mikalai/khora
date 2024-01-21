#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IRenameEntryMessage.h>

namespace Vandrouka::State::Private::Messages {

class RenameEntryMessage
    : public Fundamental::Private::MessageBase<RenameEntryMessage, State::Messages::IRenameEntryMessage> {

public:
  RenameEntryMessage(Catalog::EntryPath _oldPath, Catalog::EntryPath _newPath)
      : _oldPath(_oldPath), _newPath(_newPath) {}

  Catalog::EntryPath GetOldPath() const override { return _oldPath; }
  Catalog::EntryPath GetNewPath() const override { return _newPath; }

private:
  Catalog::EntryPath _oldPath;
  Catalog::EntryPath _newPath;
};

} // namespace Vandrouka