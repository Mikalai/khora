#include "SaveToFileMessageProcessor.h"
#include <Serializer/Interface/ISerializable.h>

namespace Vandrouka::State::Private::Processors {

void SaveToFileMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<State::Messages::ISaveToFileMessage> cmd,
    Ref<IMessageOutput> sink) {

  auto j = Create<Instances::Serializer::JsonPackage, Serializer::IPackage>();
  auto writer = j->GetWriter();
  {
    auto packages = writer->BeginArray("packages");

    for (auto &[name, info] : state->GetPackages()) {
      auto package = packages->BeginPackage();
      package->Write("name", name);
      package->Write("path", info.Path);
      packages->EndPackage();
    }
    writer->EndArray();
  }

  {
    auto catalog = writer->BeginPackage("catalog");
    auto scene = state->GetDir()
                     ->FindEntry({ROOT_SCENE})
                     .Cast<Serializer::ISerializable>();
    assert(scene);
    scene->Serialize(catalog.Value(), {});
    writer->EndPackage();
  }

  {
    auto dir = writer->BeginPackage("config");
    auto config = state->GetDir()
                      ->FindEntry({ROOT_CONFIG})
                      .Cast<Serializer::ISerializable>();
    assert(config);
    config->Serialize(dir.Value(), {});
    writer->EndPackage();
  }

  j->WriteToFile(cmd->GetPath());
}

} // namespace Vandrouka::State::Private::Processors