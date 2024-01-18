#include "ResetModelMessageProcessor.h"
#include "../../IGroupEntry.h"
#include "../../ISharedEntry.h"
#include "../../Messages/ConfigChangedMessage.h"
#include "../../Messages/ModelResetMessage.h"

namespace Vandrouka {

void ResetModelMessageProcessor::ProcessMessage(Ref<IDataModelState> state,
                                                Ref<IResetModelMessage> cmd,
                                                Ref<IMessageOutput> sink) {

  state->SetDir(Create<GroupEntry, IDirectoryEntry>());
  sink->SubmitAllMessages(state->GetDir()->Add({ROOT_CONFIG}, Create<ConfigEntry, IEntry>()).Value().Added);
  state->ClearPackages();  

  sink->SubmitMessage(new ModelResetMessage{state->GetDir()});

  auto cfg = state->GetConfig();
  if (auto s = cfg.Cast<ISharedEntry>(); s) {
    sink->SubmitMessage(new ConfigChangedMessage{
        s->CreateShared(state->GetSyncContext()).Cast<IConfigEntry>()});
  } else {
    sink->SubmitMessage(new ConfigChangedMessage{cfg});
  }
}

} // namespace Vandrouka