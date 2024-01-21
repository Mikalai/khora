#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/ICompilationState.h>
#include <State/Interface/Messages/IFontsCompilationJobsCompleteMessage.h>

namespace Vandrouka::State::Private::Messages {

class FontsCompilationJobsCompleteMessage
    : public Fundamental::Private::MessageBase<
          FontsCompilationJobsCompleteMessage,
          State::Messages::IFontsCompilationJobsCompleteMessage> {
public:
  FontsCompilationJobsCompleteMessage(const Ref<ICompilationState> &_state)
      : _state(_state) {}

  Ref<ICompilationState> GetState() const { return _state; }

private:
  Ref<ICompilationState> _state;
};

} // namespace Vandrouka::State::Private::Messages
