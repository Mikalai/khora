#pragma once

#include <Fonts/Interface/Messages/IRefreshFontsMessage.h>
#include <Fonts/Module/ISystemFontsPrivate.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::Fonts::Private::Processors {

class RefreshFontsProcessor : public Fundamental::Private::MessageProcessorBase<
                                  RefreshFontsProcessor, ISystemFontsPrivate,
                                  Fonts::Messages::IRefreshFontsMessage> {

public:
  void ProcessMessage(Ref<ISystemFontsPrivate> state,
                      Ref<Fonts::Messages::IRefreshFontsMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::Fonts::Private::Processor
