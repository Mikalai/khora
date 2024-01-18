#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class SaveToFileMessage
    : public MessageBase<SaveToFileMessage, ISaveToFileMessage> {
public:
  SaveToFileMessage(const std::filesystem::path &_path) : _path(_path) {}

  std::filesystem::path GetPath() const override { return _path; }

private:
  std::filesystem::path _path;
};

} // namespace Vandrouka