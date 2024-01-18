#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {

class ImportFileMessage
    : public MessageBase<ImportFileMessage, IImportFileMessage> {
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

} // namespace Vandrouka