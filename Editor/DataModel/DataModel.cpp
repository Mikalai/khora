#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/bind/bind.hpp>
#include <boost/dll.hpp>
#include <codecvt>
#include <filesystem>
#include <iostream>
#include <magic_enum.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <queue>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>
#include <vsg/all.h>

#include "../DirectoryEntry.h"
#include "../GroupEntry.h"
#include "../IDataModel.h"
#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IEntryObserver.h"
#include "../Messages/ModelResetMessage.h"
#include "../Observer.h"
#include "../SystemFonts.h"
#include "DataModel.h"
#include "DataModelState.h"
#include "Processors.h"

namespace Vandrouka {

class ISystemFonts;
class CompilationState;
class TextEntry;

class DataModel final
    : public ObservableBase<DataModel, IDataModel, IDataModelState,
                            IMessageOutput, IObserver> {

public:
  using Interfaces =
      QueryInterfaces<DataModel, IDataModel, IDataModelState, IMessageOutput,
                      IObserver, IObservable, IReferenced>;

public:
  DataModel() {
    _statePtr = new DataModelState{GetSyncContext(), (IMessageOutput *)this};

    _processor = new AggregatedProcessorAsync{GetSyncContext()};    
    _processor->AddProcessor(new CompileSceneProcessor());
    _processor->AddProcessor(new CopyNodeMessageProcessor());
    _processor->AddProcessor(new MoveEntryMessageProcessor());
    _processor->AddProcessor(new CopyEntryMessageProcessor());
    _processor->AddProcessor(new RemoveEntryMessageProcessor());
    _processor->AddProcessor(new SaveToFileMessageProcessor());
    _processor->AddProcessor(new ImportFileMessageProcessor());
    _processor->AddProcessor(new ImportFromFileMessageProcessor());
    _processor->AddProcessor(new ResetModelMessageProcessor());
    _processor->AddProcessor(new SelectEntryMessageProcessor());
    _processor->AddProcessor(new CreateNodeMessageProcessor());
    _processor->AddProcessor(new ExportToFileMessageProcessor());
    _processor->AddProcessor(new RequestSuggestedChildrenMessageProcessor());
    _processor->AddProcessor(new AddLanguageMessageProcessor());
    _processor->AddProcessor(new RemoveLanguageMessageProcessor());
    _processor->AddProcessor(new RenameLanguageMessageProcessor());
    _processor->AddProcessor(new SetActiveLanguageMessageProcessor());
    _processor->AddProcessor(new Data::Processors::FontCompiledMessageProcessor());
    _processor->AddProcessor(new FontsCompilationJobsCompleteMessageProcessor());
    _processor->SetUnhandledProcessor(new UnhandledMessageProcessor());

    _statePtr->CreateAxis();
    OnNext(new ModelResetMessage{_statePtr->GetDir()});
  }

  void Execute(Ref<IMessage> msg) override {    
    _processor->Process(static_cast<IDataModelState *>(this), msg,
                        static_cast<IMessageOutput *>(this));
  }

  void OnNext(Ref<IMessage> msg) override { Execute(msg); }
  void OnError(Ref<IError> error) override { RaiseError(error); }
  void OnComplete() override {}

  void DenyCompilation() override { _statePtr->DenyCompilation(); }
  void AllowCompilation() override { _statePtr->AllowCompilation(); }
  bool CanCompile() const override { return _statePtr->CanCompile(); }
  Ref<ISystemFonts> GetFonts() override { return _statePtr->GetFonts(); }

  vsg::ref_ptr<vsg::Node> FindPreviewPackage(std::string_view name) override {
    return _statePtr->FindPreviewPackage(name);
  }
  void AddPreviewPackage(std::string_view name, PackageInfo info) override {
    _statePtr->AddPreviewPackage(name, info);
  }

  Ref<IDirectoryEntry> GetDir() override { return _statePtr->GetDir(); }
  void SetDir(Ref<IDirectoryEntry> dir) override { _statePtr->SetDir(dir); }
  Ref<IEntry> GetActiveEntry() override { return _statePtr->GetActiveEntry(); }
  void SetActiveEntry(Ref<IEntry> entry) override {
    _statePtr->SetActiveEntry(entry);
  }
  vsg::ref_ptr<vsg::Node> GetAxis() override { return _statePtr->GetAxis(); }
  std::unordered_map<std::string, PackageInfo> GetPackages() const override {
    return _statePtr->GetPackages();
  }
  vsg::ref_ptr<vsg::Options> GetOptions() const override {
    return _statePtr->GetOptions();
  }

  void ClearPackages() override { _statePtr->ClearPackages(); }

private:
  void SubmitMessage(Ref<IMessage> msg) override { RaiseMessage(msg); }
  void SubmitError(Ref<IError> msg) override { RaiseError(msg); }

  Ref<IConfigEntry> GetConfig() { return _statePtr->GetConfig(); }

  void AddDependency(Ref<IReferenced> d) override {
    if (auto fonts = d.Cast<ISystemFonts>(); fonts) {
      _statePtr->_fonts = fonts;
      if (auto o = fonts.Cast<IObservable>(); o) {
        _statePtr->_fontsSubscription = o->Subscribe(this);
      }
    }
  }

private:
  Ref<DataModelState> _statePtr;
  Ref<IAggregatedProcessor> _processor;
};

IReferenced *CreateDataModel() {
  // static_assert(std::derived_from<::Vandrouka::AsyncQueue, IReferenced>,
  // "AsyncQueue is not IReferenced");
  return (IDataModel *)(new DataModel());
}

} // namespace Vandrouka
