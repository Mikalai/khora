#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class RequestSuggestedChildrenMessage
    : public MessageBase<RequestSuggestedChildrenMessage,
                         IRequestSuggestedChildrenMessage> {
public:
  RequestSuggestedChildrenMessage(EntryPath path, std::string ctx)
      : _path{path}, _ctx{ctx} {}

  const EntryPath &GetPath() const override { return _path; }
  const std::string &GetContext() const override { return _ctx; }

private:
  EntryPath _path;
  std::string _ctx;
};

} // namespace Vandrouka