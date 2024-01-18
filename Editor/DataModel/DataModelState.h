#pragma once

#include "../IGroupEntry.h"
#include "IDataModelState.h"

namespace Vandrouka {

class DataModelState
    : public ReferenceCountedBase<DataModelState, IDataModelState> {
public:
  DataModelState(Ref<IAsyncQueue> queue, IReferenced *owner);

  Ref<IAsyncQueue> GetSyncContext() { return _queue; }

  Ref<IAsyncQueue> _queue;
  IReferenced *_owner;
  Ref<IDirectoryEntry> _dir = Create<GroupEntry, IDirectoryEntry>();
  std::unordered_map<std::string, PackageInfo> _packagePreviewRoots;
  Ref<IReferenced> _dirSubscription;
  EntryRef _activeEntry;
  vsg::ref_ptr<vsg::Options> _options = vsg::Options::create();
  std::int32_t _denyCompilation{0};
  Ref<ISystemFonts> _fonts;
  Ref<IReferenced> _fontsSubscription;
  vsg::StateInfo stateInfo;
  vsg::ref_ptr<vsg::Builder> _builder = vsg::Builder::create();
  vsg::ref_ptr<vsg::Group> _axis;

  vsg::ref_ptr<vsg::Options> GetOptions() const override;

  void ClearPackages() override;

  Ref<IConfigEntry> GetConfig() override;

  void SetDir(Ref<IDirectoryEntry> dir) override;

  vsg::ref_ptr<vsg::Node> GetAxis() override;

  Ref<ISystemFonts> GetFonts() override;

  std::unordered_map<std::string, PackageInfo> GetPackages() const override;

  vsg::ref_ptr<vsg::Node> FindPreviewPackage(std::string_view name);

  void AddPreviewPackage(std::string_view name, PackageInfo info) override;

  void DenyCompilation() override;

  void AllowCompilation() override;

  bool CanCompile() const override;

  Ref<IDirectoryEntry> GetDir() override;

  Ref<IEntry> GetActiveEntry() override;

  void SetActiveEntry(Ref<IEntry> entry) override;

  void CreateAxis();

  // Inherited via ReferenceCountedBase
  void Execute(Ref<IMessage> msg) override;
};

} // namespace Vandrouka