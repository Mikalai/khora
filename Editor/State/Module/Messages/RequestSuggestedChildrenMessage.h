#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IRequestSuggestedChildrenMessage.h>

namespace Vandrouka::State::Private::Messages {

class RequestSuggestedChildrenMessage
    : public Fundamental::Private::MessageBase<RequestSuggestedChildrenMessage,
                         State::Messages::IRequestSuggestedChildrenMessage> {
public:
  RequestSuggestedChildrenMessage(Catalog::EntryPath path, std::string ctx)
      : _path{path}, _ctx{ctx} {}

  const Catalog::EntryPath &GetPath() const override { return _path; }
  const std::string &GetContext() const override { return _ctx; }

private:
  Catalog::EntryPath _path;
  std::string _ctx;
};

} // namespace Vandrouka