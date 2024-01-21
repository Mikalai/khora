#pragma once

#include <Fundamental/Interface/IMessage.h>
#include <State/Interface/ICompilationState.h>

namespace Vandrouka::State::Messages {

class IFontsCompilationJobsCompleteMessage : public IMessage {
public:
  virtual Ref<ICompilationState> GetState() const = 0;
};

} // namespace Vandrouka::State::Messages

DECLARE_IID(Vandrouka::State::Messages::IFontsCompilationJobsCompleteMessage,
            0x5d, 0x64, 0xfa, 0x92, 0xf3, 0xc9, 0x40, 0x58, 0x97, 0x71, 0x6c,
            0x54, 0x27, 0x64, 0xcc, 0x4a);