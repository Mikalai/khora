#pragma once

#include <Fundamental/Interface/IAsyncQueue.h>
#include <Fundamental/Interface/IMessage.h>
#include <Fundamental/Module/Referenced.h>
#include <State/Interface/IDataModelState.h>

namespace Vandrouka::State::Private {

class DataModelState
    : public Fundamental::Private::ReferenceCountedBase<DataModelState,
                                                        IDataModelState> {
public:
  DataModelState(Ref<IAsyncQueue> queue, IReferenced *owner);

  Ref<IAsyncQueue> GetSyncContext() { return _queue; }

  Ref<IAsyncQueue> _queue;
  IReferenced *_owner;
  Ref<Catalog::IDirectoryEntry> _dir =
      Create<Instances::Catalog::GroupEntry, Catalog::IDirectoryEntry>();
  std::unordered_map<std::string, PackageInfo> _packagePreviewRoots;
  Ref<IReferenced> _dirSubscription;
  Catalog::EntryRef _activeEntry;
  vsg::ref_ptr<vsg::Options> _options = vsg::Options::create();
  std::int32_t _denyCompilation{0};
  Ref<Fonts::ISystemFonts> _fonts;
  Ref<IReferenced> _fontsSubscription;
  vsg::StateInfo stateInfo;
  vsg::ref_ptr<vsg::Builder> _builder = vsg::Builder::create();
  vsg::ref_ptr<vsg::Group> _axis;

  vsg::ref_ptr<vsg::Options> GetOptions() const override;

  void ClearPackages() override;

  Ref<Catalog::IConfigEntry> GetConfig() override;

  void SetDir(Ref<Catalog::IDirectoryEntry> dir) override;

  vsg::ref_ptr<vsg::Node> GetAxis() override;

  Ref<Fonts::ISystemFonts> GetFonts() override;

  std::unordered_map<std::string, PackageInfo> GetPackages() const override;

  vsg::ref_ptr<vsg::Node> FindPreviewPackage(std::string_view name);

  void AddPreviewPackage(std::string_view name, PackageInfo info) override;

  void DenyCompilation() override;

  void AllowCompilation() override;

  bool CanCompile() const override;

  Ref<Catalog::IDirectoryEntry> GetDir() override;

  Ref<Catalog::IEntry> GetActiveEntry() override;

  void SetActiveEntry(Ref<Catalog::IEntry> entry) override;

  void CreateAxis();

  // Inherited via ReferenceCountedBase
  void Execute(Ref<IMessage> msg) override;
};

} // namespace Vandrouka::State::Private
