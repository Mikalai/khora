#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/IImportFileMessage.h>

namespace Vandrouka::State::Private::Messages {

class ImportFileMessage
    : public Fundamental::Private::MessageBase<
          ImportFileMessage, State::Messages::IImportFileMessage> {
public:
  ImportFileMessage(std::string path, vsg::ref_ptr<vsg::Options> options,
                    std::filesystem::path filePath)
      : _path{path}, _options{options}, _filePath{filePath} {}

  const std::string &GetFilePath() const override { return _path; }

  vsg::ref_ptr<vsg::Options> GetOptions() const override { return _options; }

  const std::filesystem::path &GetProjectPath() const override {
    return _filePath;
  }

private:
  std::string _path;
  vsg::ref_ptr<vsg::Options> _options;
  std::filesystem::path _filePath;
};

} // namespace Vandrouka::State::Private::Messages