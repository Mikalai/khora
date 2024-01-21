#pragma once

#include <Fonts/Interface/Messages/ICompileFontMessage.h>
#include <Fonts/Module/ISystemFontsPrivate.h>
#include <Fundamental/Interface/IMessageOutput.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::Fonts::Private::Processors {

class CompileFontsProcessor : public Fundamental::Private::MessageProcessorBase<
                                  CompileFontsProcessor, ISystemFontsPrivate,
                                  Fonts::Messages::ICompileFontMessage> {

public:
  void ReportMessage(Ref<IMessage> msg, Ref<IReferenced> observer,
                     Ref<IMessageOutput> output);

  void ProcessMessage(Ref<ISystemFontsPrivate> state,
                      Ref<Fonts::Messages::ICompileFontMessage> cmd,
                      Ref<IMessageOutput> sink);
};

} // namespace Vandrouka::Fonts::Private::Processor
