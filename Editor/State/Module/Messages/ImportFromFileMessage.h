#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IImportFromFileMessage.h>

namespace Vandrouka::State::Private::Messages {

class ImportFromFileMessage
    : public Fundamental::Private::MessageBase<
          ImportFromFileMessage, State::Messages::IImportFromFileMessage> {
public:
  ImportFromFileMessage(std::filesystem::path path) : _path{path} {}

  std::filesystem::path GetPath() const override { return _path; }

private:
  std::filesystem::path _path;
};

} // namespace Vandrouka::State::Private::Messages
