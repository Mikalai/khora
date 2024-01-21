#pragma once

#include <Catalog/Interface/EntryPath.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IRequestSuggestedChildrenMessage : public IMessage {
public:
  virtual const Catalog::EntryPath &GetPath() const = 0;
  virtual const std::string &GetContext() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IRequestSuggestedChildrenMessage, 0x93,
            0x32, 0xee,
            0x1c, 0xd1, 0x1a, 0x4b, 0x40, 0x8f, 0x82, 0x30, 0xa8, 0x40, 0xe9,
            0x86, 0xd1);
