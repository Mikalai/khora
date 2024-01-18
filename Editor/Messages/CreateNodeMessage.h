#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class CreateNodeMessage
    : public MessageBase<CreateNodeMessage, ICreateNodeMessage> {
public:
  CreateNodeMessage(EntryPath path, std::string type)
      : _path{path}, _type{type} {}

  EntryPath GetPath() const override { return _path; }
  std::string GetType() const override { return _type; }

private:
  EntryPath _path;
  std::string _type;
};

} // namespace Vandrouka