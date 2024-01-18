#include "ImportFileMessageProcessor.h"
#include "../../LongOperationNotification.h"
#include "../../IGroupEntry.h"
#include "../../ISerializable.h"
#include "../../Messages/ImportFileMessage.h"
#include "../../Messages/CompileMessage.h"
#include "../../../Render/WorldCompiler.h"
#include "../../IMaterialEntry.h"
#include "../../IGeometryEntry.h"
#include "../../ITransformEntry.h"
#include "../../IPackageEntry.h"

namespace Vandrouka {

void ImportFileMessageProcessor::ProcessMessage(Ref<IDataModelState> model,
                                                Ref<IImportFileMessage> cmd,
                                                Ref<IMessageOutput> sink) {

  LongOperationScope op{*sink.Get(), &IMessageOutput::SubmitMessage,
                        LongOperation{.Name = "Import " + cmd->GetFilePath()}};

  model->DenyCompilation();

  auto importFile = [&]() {
    std::filesystem::path requestedPath = cmd->GetFilePath();
    auto newPath = cmd->GetProjectPath() / "Raw" / requestedPath.filename();
    std::error_code ec;
    if (!std::filesystem::equivalent(requestedPath.parent_path(), newPath, ec)) {
      auto oldPath = requestedPath;
      if (oldPath.is_relative()) {
        oldPath = cmd->GetProjectPath() / oldPath;
      }
      if (oldPath != newPath) {
        std::error_code ec;
        if (!std::filesystem::copy_file(
                oldPath, newPath,
                std::filesystem::copy_options::overwrite_existing, ec)) {
          sink->SubmitError(
              new GenericError{LOG_LEVEL_ERROR, LOG_IO_ERROR, ec.message()});
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

      Ref<IAsyncTask> completion{new CallbackTask([&]() {})};

      sink->SubmitMessage(new CompileMessage{root, completion});

      auto packageName = std::filesystem::path(relPath).filename().string();

      model->AddPreviewPackage(packageName, {.Path = relPath, .Root = root});

      WorldCompiler compiler;
      root->accept(compiler);

      for (auto &o : compiler.objects) {
        std::string path = o.first;

        if (auto tr = std::get<0>(o.second).cast<vsg::MatrixTransform>(); tr) {

          auto node = Create<TransformPackageEntry, IPackageEntry>()
                          ->SetData(tr)
                          .Cast<IEntry>();

          sink->SubmitAllMessages(model->GetDir()->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                                PACKAGE_ENTRY_TRANSFORMS + "/" + o.first},
                               node).Value().Added);

          for (auto child : tr->children) {
            if (auto m = child.cast<vsg::StateGroup>(); m) {
              auto node = Create<MaterialPackageEntry, IPackageEntry>()
                              ->SetData(m)
                              .Cast<IEntry>();

              sink->SubmitAllMessages(model->GetDir()->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                                    PACKAGE_ENTRY_MATERIALS + "/" + o.first},
                                   node).Value().Added);
            }
          }
        }

        if (auto tr = std::get<0>(o.second).cast<vsg::VertexIndexDraw>(); tr) {

          auto node = Create<GeometryPackageEntry, IPackageEntry>()
                          ->SetData(tr)
                          .Cast<IEntry>();

          sink->SubmitAllMessages(model->GetDir()->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                                PACKAGE_ENTRY_GEOMETRIES + "/" + path},
                               node).Value().Added);
        }

        if (auto tr = std::get<0>(o.second).cast<vsg::StateGroup>(); tr) {
          auto node = Create<MaterialPackageEntry, IPackageEntry>()
                          ->SetData(tr)
                          .Cast<IEntry>();

          sink->SubmitAllMessages(model->GetDir()->Add({ROOT_PACKAGES + "/" + packageName + "/" +
                                PACKAGE_ENTRY_MATERIALS + "/" + path},
                               node).Value().Added);
        }
      }
    }
  };

  importFile();
  model->AllowCompilation();
}

} // namespace Vandrouka
