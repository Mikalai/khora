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

#include <Catalog/Module/DirectoryEntry.h>
#include <Catalog/Module/GroupEntry.h>
#include <State/Interface/IDataModel.h>

#include <Fonts/Interface/ISystemFonts.h>
#include <Fundamental/Module/Observer.h>
#include <State/Module/Messages/ModelResetMessage.h>

#include "DataModel.h"
#include "DataModelState.h"
#include "Processors.h"

namespace Vandrouka::State::Private {

class DataModel final
    : public Fundamental::Private::ObservableBase<
          DataModel, IDataModel, IDataModelState, IMessageOutput, IObserver> {

public:
  using Interfaces = Fundamental::Private::QueryInterfaces<
      DataModel, IDataModel, IDataModelState, IMessageOutput, IObserver,
      IObservable, IReferenced>;

public:
  DataModel() {
    _statePtr = new DataModelState{GetSyncContext(), (IMessageOutput *)this};

    _processor =
        new Fundamental::Private::AggregatedProcessorAsync{GetSyncContext()};
    _processor->AddProcessor(new Processors::CompileSceneProcessor());
    _processor->AddProcessor(new Processors::CopyNodeMessageProcessor());
    _processor->AddProcessor(new Processors::MoveEntryMessageProcessor());
    _processor->AddProcessor(new Processors::CopyEntryMessageProcessor());
    _processor->AddProcessor(new Processors::RemoveEntryMessageProcessor());
    _processor->AddProcessor(new Processors::SaveToFileMessageProcessor());
    _processor->AddProcessor(new Processors::ImportFileMessageProcessor());
    _processor->AddProcessor(new Processors::ImportFromFileMessageProcessor());
    _processor->AddProcessor(new Processors::ResetModelMessageProcessor());
    _processor->AddProcessor(new Processors::SelectEntryMessageProcessor());
    _processor->AddProcessor(new Processors::CreateNodeMessageProcessor());
    _processor->AddProcessor(new Processors::ExportToFileMessageProcessor());
    _processor->AddProcessor(
        new Processors::RequestSuggestedChildrenMessageProcessor());
    _processor->AddProcessor(new Processors::AddLanguageMessageProcessor());
    _processor->AddProcessor(new Processors::RemoveLanguageMessageProcessor());
    _processor->AddProcessor(new Processors::RenameLanguageMessageProcessor());
    _processor->AddProcessor(
        new Processors::SetActiveLanguageMessageProcessor());
    _processor->AddProcessor(new Processors::FontCompiledMessageProcessor());
    _processor->AddProcessor(
        new Processors::FontsCompilationJobsCompleteMessageProcessor());
    _processor->SetUnhandledProcessor(new UnhandledMessageProcessor());

    _statePtr->CreateAxis();
    OnNext(new Messages::ModelResetMessage{_statePtr->GetDir()});
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
  Ref<Fonts::ISystemFonts> GetFonts() override { return _statePtr->GetFonts(); }

  vsg::ref_ptr<vsg::Node> FindPreviewPackage(std::string_view name) override {
    return _statePtr->FindPreviewPackage(name);
  }
  void AddPreviewPackage(std::string_view name, PackageInfo info) override {
    _statePtr->AddPreviewPackage(name, info);
  }

  Ref<Catalog::IDirectoryEntry> GetDir() override {
    return _statePtr->GetDir();
  }
  void SetDir(Ref<Catalog::IDirectoryEntry> dir) override {
    _statePtr->SetDir(dir);
  }
  Ref<Catalog::IEntry> GetActiveEntry() override {
    return _statePtr->GetActiveEntry();
  }
  void SetActiveEntry(Ref<Catalog::IEntry> entry) override {
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

  Ref<Catalog::IConfigEntry> GetConfig() { return _statePtr->GetConfig(); }

  void AddDependency(Ref<IReferenced> d) override {
    if (auto fonts = d.Cast<Fonts::ISystemFonts>(); fonts) {
      _statePtr->_fonts = fonts;
      if (auto o = fonts.Cast<IObservable>(); o) {
        _statePtr->_fontsSubscription = o->Subscribe(this);
      }
    }
  }

private:
  Ref<DataModelState> _statePtr;
  Ref<Fundamental::IAggregatedProcessor> _processor;
};

} // namespace Vandrouka::State::Private

namespace Vandrouka::Factory {

IReferenced *CreateDataModel() {
  // static_assert(std::derived_from<::Vandrouka::AsyncQueue, IReferenced>,
  // "AsyncQueue is not IReferenced");
  return (State::IDataModel *)(new State::Private::DataModel());
}

} // namespace Vandrouka::Factory