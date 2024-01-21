#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ISaveToFileMessage.h>

namespace Vandrouka::State::Private::Messages {

class SaveToFileMessage
    : public Fundamental::Private::MessageBase<SaveToFileMessage, State::Messages::ISaveToFileMessage> {
public:
  SaveToFileMessage(const std::filesystem::path &_path) : _path(_path) {}

  std::filesystem::path GetPath() const override { return _path; }

private:
  std::filesystem::path _path;
};

} // namespace Vandrouka