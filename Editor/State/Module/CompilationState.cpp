//#include "CompilationState.h"
//#include "../ISystemFonts.h"
//
//namespace Vandrouka {
//
//void CompilationState::OnNext(Ref<IMessage> msg) {
//  if (auto fnt = msg.Cast<IFontCompiledMessage>(); fnt) {
//    OnFontCompiled(fnt->GetDisplayName(), fnt->GetFont());
//  };
//}
//
//void CompilationState::OnFontCompiled(const std::string &name,
//                                      vsg::ref_ptr<vsg::Font> font) {  
//    UsedFonts[name] = font;
//    if (requestedFontCompilations == 0) {
//      auto root = Compile(state->RootPath, state, state->Root);
//      Notify(IDataModelObserver::SceneCompeledNotification{.Root = root});
//    }
//  }
//}
//
//void CompilationState::OnError(Ref<IError> error) {}
//
//void CompilationState::OnComplete() {}
//
//} // namespace Vandrouka