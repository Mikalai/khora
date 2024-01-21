#include "ResetModelMessageProcessor.h"
#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Interface/ISharedEntry.h>
#include <State/Module/Messages/ConfigChangedMessage.h>
#include <State/Module/Messages/ModelResetMessage.h>

namespace Vandrouka::State::Private::Processors {

void ResetModelMessageProcessor::ProcessMessage(Ref<IDataModelState> state, Ref<State::Messages::IResetModelMessage> cmd,
                                                Ref<IMessageOutput> sink) {

  state->SetDir(Create<Instances::Catalog::GroupEntry, Catalog::IDirectoryEntry>());
  sink->SubmitAllMessages(state->GetDir()->Add({ROOT_CONFIG}, Create<Instances::Catalog::ConfigEntry, Catalog::IEntry>()).Value().Added);
  state->ClearPackages();  

  sink->SubmitMessage(new Messages::ModelResetMessage{state->GetDir()});

  auto cfg = state->GetConfig();
  if (auto s = cfg.Cast<Catalog::ISharedEntry>(); s) {
    sink->SubmitMessage(new Messages::ConfigChangedMessage{
        s->CreateShared(state->GetSyncContext()).Cast<Catalog::IConfigEntry>()});
  } else {
    sink->SubmitMessage(new Messages::ConfigChangedMessage{cfg});
  }
}

} // namespace Vandrouka::State::Private