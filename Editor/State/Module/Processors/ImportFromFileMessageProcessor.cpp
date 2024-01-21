#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Module/Messages/EntryAddedMessage.h>
#include <Fundamental/Interface/Messages/ILongOperationEndedMessage.h>
#include <Fundamental/Module/LongOperationScope.h>
#include <Serializer/Interface/ISerializable.h>
#include <State/Module/Messages/ImportFileMessage.h>

#include "ImportFromFileMessageProcessor.h"

namespace Vandrouka::State::Private::Processors {

void ImportFromFileMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state,
    Ref<State::Messages::IImportFromFileMessage> cmd,
    Ref<IMessageOutput> sink) {

  auto onError = [sink](Ref<IError> error) mutable {
    sink->SubmitError(error);
  };

  Fundamental::Private::LongOperationScope op{
      *sink.Get(), &IMessageOutput::SubmitMessage,
      LongOperation{.Name = "Import " + cmd->GetPath().string()}};

  {
    // Ensure required folders exists
    auto parent = std::filesystem::path(cmd->GetPath()).parent_path();
    auto rawFolder = parent / "Raw";
    if (!std::filesystem::exists(rawFolder)) {
      std::filesystem::create_directory(rawFolder);
    }
  }

  auto package =
      Create<Instances::Serializer::JsonPackage, Serializer::IPackage>();
  CHECK(package->ReadFromFile(cmd->GetPath()));
  auto reader = CHECK(package->GetReader()).Value();
  assert(reader);

  {
    auto catalog = CHECK(reader->ReadArray("packages")).Value();
    for (int i = 0; i < catalog->GetSize(); ++i) {
      auto o = catalog->PackageAt(i);
      auto name = CHECK(o->ReadString("name")).Value();
      auto path = CHECK(o->ReadString("path")).Value();

      state->Execute(new Messages::ImportFileMessage{
          path, state->GetOptions(), cmd->GetPath().parent_path()});
    }
  }

  {
    auto catalog = CHECK(reader->ReadPackage("catalog"));
    auto scene =
        Create<Instances::Catalog::GroupEntry, Catalog::IDirectoryEntry>();
    assert(scene);
    CHECK(scene.Cast<Serializer::ISerializable>()->Deserialize(catalog.Value(),
                                                               {}));
    sink->SubmitAllMessages(
        state->GetDir()->Add({ROOT_SCENE}, scene).Value().Added);
  }

  {
    auto config = CHECK(reader->ReadPackage("config"));
    auto cfg = state->GetDir()->FindEntry({ROOT_CONFIG});
    assert(cfg);
    CHECK(
        cfg.Cast<Serializer::ISerializable>()->Deserialize(config.Value(), {}));
  }
}
} // namespace Vandrouka::State::Private::Processors