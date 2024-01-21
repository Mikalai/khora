#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IExportToFileMessage.h>

namespace Vandrouka::State::Private::Messages {

class ExportToFileMessage
    : public Fundamental::Private::MessageBase<ExportToFileMessage, State::Messages::IExportToFileMessage> {
public:
  ExportToFileMessage(std::string path) : _path{path} {}

  std::string GetPath() const override { return _path; };

private:
  std::string _path;
};

} // namespace Vandrouka