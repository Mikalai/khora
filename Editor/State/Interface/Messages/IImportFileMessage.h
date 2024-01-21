#pragma once

#include <vsg/all.h>

#include <filesystem>
#include <string>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::State::Messages {

class IImportFileMessage : public IMessage {
public:
  virtual const std::string &GetFilePath() const = 0;
  virtual vsg::ref_ptr<vsg::Options> GetOptions() const = 0;
  virtual const std::filesystem::path &GetProjectPath() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IImportFileMessage, 0x69, 0xb7, 0xa4,
            0x98, 0x79, 0x18, 0x46, 0xe, 0x8c, 0xb8, 0x49, 0x6b, 0xe9, 0x2,
            0xaa, 0x48);