#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ICreateNodeMessage.h>

namespace Vandrouka::State::Private::Messages {

class CreateNodeMessage
    : public Fundamental::Private::MessageBase<CreateNodeMessage,
                                               State::Messages::ICreateNodeMessage> {
public:
  CreateNodeMessage(Catalog::EntryPath path, std::string type)
      : _path{path}, _type{type} {}

  Catalog::EntryPath GetPath() const override { return _path; }
  std::string GetType() const override { return _type; }

private:
  Catalog::EntryPath _path;
  std::string _type;
};

} // namespace Vandrouka::State::Private::Messages