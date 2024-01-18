#pragma once

#include "../IDataModelState.h"
#include "../../IDataModelEditor.h"
#include "../../IDataModelObserver.h"
#include "../../MessageProcessor.h"
#include "../ICompilationState.h"

namespace Vandrouka {

class CompileSceneProcessor
    : public MessageProcessorBase<CompileSceneProcessor, IDataModelState,
                                  ICompileSceneMessage> {
public:
  void ProcessMessage(Ref<IDataModelState> model, Ref<ICompileSceneMessage> cmd,
                      Ref<IMessageOutput> sink);

  static vsg::ref_ptr<vsg::Node> Compile(EntryPath path,
                                         Ref<ICompilationState> state,
                                         EntryRef entry,
                                         Ref<IMessageOutput> sink);
  static vsg::ref_ptr<vsg::Text> CompileText(TextConfig &cfg);
  static void CompileFonts(Ref<IDataModelState> model,
                           Ref<ICompilationState> state, EntryRef entry);
};

} // namespace Vandrouka