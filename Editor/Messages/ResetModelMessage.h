#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class ResetModelMessage
    : public MessageBase<ResetModelMessage, IResetModelMessage> {};

class ImportFromFileMessage
    : public MessageBase<ImportFromFileMessage, IImportFromFileMessage> {
public:
  ImportFromFileMessage(std::filesystem::path path) : _path{path} {}

  std::filesystem::path GetPath() const override { return _path; }

private:
  std::filesystem::path _path;
};

} // namespace Vandrouka