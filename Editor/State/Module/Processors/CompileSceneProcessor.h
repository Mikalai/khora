#pragma once

#include <State/Interface/IDataModelState.h>
#include <State/Interface/ICompilationState.h>
#include <State/Interface/Messages/ICompileSceneMessage.h>
#include <Fundamental/Module/MessageProcessor.h>

namespace Vandrouka::State::Private::Processors {

class CompileSceneProcessor
    : public Fundamental::Private::MessageProcessorBase<CompileSceneProcessor, IDataModelState,
                                  State::Messages::ICompileSceneMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> model,
                      Ref<State::Messages::ICompileSceneMessage> cmd,
                      Ref<IMessageOutput> sink);

  static vsg::ref_ptr<vsg::Node> Compile(Catalog::EntryPath path, Ref<State::ICompilationState> state,
          Catalog::EntryRef entry,
                                         Ref<IMessageOutput> sink);
  static vsg::ref_ptr<vsg::Text> CompileText(TextConfig &cfg);
  static void CompileFonts(Ref<IDataModelState> model,
                           Ref<State::ICompilationState> state, Ref<Catalog::IEntry> entry);
};

} // namespace Vandrouka::State::Private