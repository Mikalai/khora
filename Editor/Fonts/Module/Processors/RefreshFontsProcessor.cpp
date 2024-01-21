#pragma once

#include "RefreshFontsProcessor.h"
#include <Fonts/Module/Messages/FontsRefreshCompletedMessage.h>

namespace Vandrouka::Fonts::Private::Processors {

void RefreshFontsProcessor::ProcessMessage(
    Ref<ISystemFontsPrivate> state,
    Ref<Fonts::Messages::IRefreshFontsMessage> cmd, Ref<IMessageOutput> sink) {
  if (cmd->GetForce() || !state->HasFonts()) {
    state->RefreshInternal();
  }

  sink->SubmitMessage(
      new Messages::FontsRefreshCompletedMessage{state->GetFonts()});
}

} // namespace Vandrouka::Fonts::Private::Processor
