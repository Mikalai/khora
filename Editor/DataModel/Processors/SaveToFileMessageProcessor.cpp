#include "../../ISerializable.h"
#include "SaveToFileMessageProcessor.h"

namespace Vandrouka {

void Vandrouka::SaveToFileMessageProcessor::ProcessMessage(
    Ref<IDataModelState> state, Ref<ISaveToFileMessage> cmd,
    Ref<IMessageOutput> sink) {

  auto j = Create<JsonPackage, IPackage>();
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
    auto scene = state->GetDir()->FindEntry({ROOT_SCENE}).Cast<ISerializable>();
    assert(scene);
    scene->Serialize(catalog.Value(), {});
    writer->EndPackage();
  }

  {
    auto dir = writer->BeginPackage("config");
    auto config =
        state->GetDir()->FindEntry({ROOT_CONFIG}).Cast<ISerializable>();
    assert(config);
    config->Serialize(dir.Value(), {});
    writer->EndPackage();
  }

  j->WriteToFile(cmd->GetPath());
}

} // namespace Vandrouka