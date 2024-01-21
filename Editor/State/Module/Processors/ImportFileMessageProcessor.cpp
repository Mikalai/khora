#include "ImportFileMessageProcessor.h"
#include "../../../Render/WorldCompiler.h"
#include <Catalog/Interface/IGeometryEntry.h>
#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Interface/IMaterialEntry.h>
#include <Catalog/Interface/IPackageEntry.h>
#include <Catalog/Interface/ITransformEntry.h>
#include <Fundamental/Interface/Messages/ILongOperationEndedMessage.h>
#include <Fundamental/Module/AsyncQueue.h>
#include <Fundamental/Module/LongOperationScope.h>
#include <Serializer/Interface/ISerializable.h>
#include <State/Module/Messages/CompileMessage.h>
#include <State/Module/Messages/ImportFileMessage.h>

namespace Vandrouka::State::Private::Processors {

void ImportFileMessageProcessor::ProcessMessage(
    Ref<IDataModelState> model, Ref<State::Messages::IImportFileMessage> cmd,
    Ref<IMessageOutput> sink) {

  Fundamental::Private::LongOperationScope op{
      *sink.Get(), &IMessageOutput::SubmitMessage,
      LongOperation{.Name = "Import " + cmd->GetFilePath()}};

  model->DenyCompilation();

  auto importFile = [&]() {
    std::filesystem::path requestedPath = cmd->GetFilePath();
    auto newPath = cmd->GetProjectPath() / "Raw" / requestedPath.filename();
    std::error_code ec;
    if (!std::filesystem::equivalent(requestedPath.parent_path(), newPath,
                                     ec)) {
      auto oldPath = requestedPath;
      if (oldPath.is_relative()) {
        oldPath = cmd->GetProjectPath() / oldPath;
      }
      if (oldPath != newPath) {
        std::error_code ec;
        if (!std::filesystem::copy_file(
                oldPath, newPath,
                std::filesystem::copy_options::overwrite_existing, ec)) {
          sink->SubmitError(CreateError(LOG_IO_ERROR, ec.message()));
          return;
        }
      }
      requestedPath = newPath;
    }

    if (requestedPath.is_relative()) {
      requestedPath = cmd->GetProjectPath() / requestedPath;
    }

    if (auto root = vsg::read_cast<vsg::Node>(requestedPath.native(),
                                              cmd->GetOptions());
        root) {
      auto relPath =
          std::filesystem::relative(requestedPath, cmd->GetProjectPath());

      Ref<IAsyncTask> completion{
          new Fundamental::Private::CallbackTask([&]() {})};

      sink->SubmitMessage(new Messages::CompileMessage{root, completion});

      auto packageName = std::filesystem::path(relPath).filename().string();

      model->AddPreviewPackage(packageName, {.Path = relPath, .Root = root});

      WorldCompiler compiler;
      root->accept(compiler);

      for (auto &o : compiler.objects) {
        std::string path = o.first;

        if (auto tr = std::get<0>(o.second).cast<vsg::MatrixTransform>(); tr) {

          auto node = Create<Instances::Catalog::TransformPackageEntry,
                             Catalog::IPackageEntry>()
                          ->SetData(tr)
                          .Cast<Catalog::IEntry>();

          sink->SubmitAllMessages(
              model->GetDir()
                  ->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                         PACKAGE_ENTRY_TRANSFORMS + "/" + o.first},
                        node)
                  .Value()
                  .Added);

          for (auto child : tr->children) {
            if (auto m = child.cast<vsg::StateGroup>(); m) {
              auto node = Create<Instances::Catalog::MaterialPackageEntry,
                                 Catalog::IPackageEntry>()
                              ->SetData(m)
                              .Cast<Catalog::IEntry>();

              sink->SubmitAllMessages(
                  model->GetDir()
                      ->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                             PACKAGE_ENTRY_MATERIALS + "/" + o.first},
                            node)
                      .Value()
                      .Added);
            }
          }
        }

        if (auto tr = std::get<0>(o.second).cast<vsg::VertexIndexDraw>(); tr) {

          auto node = Create<Instances::Catalog::GeometryPackageEntry,
                             Catalog::IPackageEntry>()
                          ->SetData(tr)
                          .Cast<Catalog::IEntry>();

          sink->SubmitAllMessages(
              model->GetDir()
                  ->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                         PACKAGE_ENTRY_GEOMETRIES + "/" + path},
                        node)
                  .Value()
                  .Added);
        }

        if (auto tr = std::get<0>(o.second).cast<vsg::StateGroup>(); tr) {
          auto node = Create<Instances::Catalog::MaterialPackageEntry,
                             Catalog::IPackageEntry>()
                          ->SetData(tr)
                          .Cast<Catalog::IEntry>();

          sink->SubmitAllMessages(
              model->GetDir()
                  ->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                         PACKAGE_ENTRY_MATERIALS + "/" + path},
                        node)
                  .Value()
                  .Added);
        }
      }
    }
  };

  importFile();
  model->AllowCompilation();
}

} // namespace Vandrouka::State::Private
