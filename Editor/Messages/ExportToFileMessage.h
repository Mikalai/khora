#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class ExportToFileMessage
    : public MessageBase<ExportToFileMessage, IExportToFileMessage> {
public:
  ExportToFileMessage(std::string path) : _path{path} {}

  std::string GetPath() const override { return _path; };

private:
  std::string _path;
};

} // namespace Vandrouka