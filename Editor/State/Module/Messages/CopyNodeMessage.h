#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ICopyNodeMessage.h>

namespace Vandrouka {

class CopyNodeMessage
    : public Fundamental::Private::MessageBase<
          CopyNodeMessage, State::Messages::ICopyNodeMessage> {
public:
  CopyNodeMessage(Catalog::EntryPath src, Catalog::EntryPath dst)
      : _src{src}, _dst{dst} {}

  Catalog::EntryPath GetSourcePath() const override { return _src; }
  Catalog::EntryPath GetTargetPath() const override { return _dst; }

private:
  Catalog::EntryPath _src;
  Catalog::EntryPath _dst;
};

} // namespace Vandrouka