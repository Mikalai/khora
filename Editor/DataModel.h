#pragma once

#include <vsg/all.h>

#include <algorithm>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/bind/bind.hpp>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "DirectoryEntry.h"
#include "GroupEntry.h"
#include "IDataModelEditor.h"
#include "IDataModelObserver.h"
#include "IEntryObserver.h"
#include "Observer.h"
#include "SystemFonts.h"

const std::string ROOT_PACKAGES{"PACKAGES"};
const std::string ROOT_SCENE{"SCENE"};
const std::string ROOT_CONFIG{"CONFIG"};

const std::string PACKAGE_ENTRY_TRANSFORMS{"Transforms"};
const std::string PACKAGE_ENTRY_GEOMETRIES{"Geometries"};
const std::string PACKAGE_ENTRY_MATERIALS{"Materials"};

class ISystemFonts;
class CompilationState;
class TextEntry;

namespace Vandrouka {

struct ImportFileCommand {
  std::string FilePath;
  vsg::ref_ptr<vsg::Options> Options;
  std::filesystem::path ProjectPath;
};

struct CompileSceneCommand {
  EntryPath Root;
};

struct CopyNodeCommand {
  EntryPath SourcePath;
  EntryPath TargetPath;
};

struct MoveEntryCommand {
  EntryPath SourcePath;
  EntryPath TargetPath;
};

struct CopyEntryCommand {
  EntryPath SourcePath;
  EntryPath TargetPath;
};

struct RemoveEntryCommand {
  EntryPath Path;
};

struct RenameEntryCommand {
  EntryPath OldPath;
  EntryPath NewPath;
};

struct SaveToFileCommand {
  std::filesystem::path Path;
};

struct ImportFromFileCommand {
  std::filesystem::path Path;
};

struct ResetModelCommand {};

struct SelectEntryCommand {
  EntryPath Path;
};

struct CreateNodeCommand {
  EntryPath Path;
  std::string Type;
};

struct ExportToFileCommand {
  std::string Path;
};

struct AddLanguageCommand {
  std::string Value;
};

struct RemoveLanguageCommand {
  std::string Value;
};

struct RenameLanguageCommand {
  std::string OldValue;
  std::string NewValue;
};

struct RequestSuggestedChildrenCommand {
  EntryPath Path;
  std::string Context;
};

struct SetActiveLanguageRequest {
  std::string Language;
};

} // namespace Vandrouka

class DataModel
    : public Observable<DataModel, IDataModelObserver, IDataModelEditor>,
      public IEntryObserver,
      public ISystemFontsObserver {
  using Base = Observable<DataModel, IDataModelObserver, IDataModelEditor>;

  friend class Observable<DataModel, IDataModelObserver, IDataModelEditor>;

protected:
  DataModel(std::shared_ptr<ISystemFonts> fonts,
            std::shared_ptr<boost::asio::io_context> ctx);

public:
  void OnCreated() override;

  virtual ~DataModel();

  void Execute(const ImportFileCommand &cmd) override;
  void Execute(const CompileSceneCommand &cmd) override;
  void Execute(const CopyNodeCommand &cmd) override;
  void Execute(const MoveEntryCommand &cmd) override;
  void Execute(const RemoveEntryCommand &cmd) override;
  void Execute(const SaveToFileCommand &cmd) override;
  void Execute(const ImportFromFileCommand &cmd) override;

  void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) override;
  void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) override;
  void OnError(const LogNotification &cmd) const override;

private:
  void CreateAxis();
  vsg::StateInfo stateInfo;
  vsg::ref_ptr<vsg::Builder> _builder = vsg::Builder::create();
  vsg::ref_ptr<vsg::Group> _axis;
  std::shared_ptr<Entry> _activeEntry;
  std::shared_ptr<ConfigEntry> GetConfig();
  std::unordered_map<std::string, FontInfo> _fontsCache;
  std::shared_ptr<ISystemFonts> _fonts;
  SubscriptionPtr _fontsSubscription;

  void CompileFonts(std::shared_ptr<CompilationState> state,
                    std::shared_ptr<Entry> entry);

  vsg::ref_ptr<vsg::Node> Compile(EntryPath path,
                                  std::shared_ptr<CompilationState> state,
                                  std::shared_ptr<Entry> entry);

  struct TextConfig {
    std::shared_ptr<TextEntry> Entry;
    vsg::ref_ptr<vsg::Font> Font;
  };

  vsg::ref_ptr<vsg::Text> CompileText(TextConfig &cfg);

  void DenyCompilation();
  void AllowCompilation();
  bool CanCompile() const { return _denyCompilation == 0; }

  struct PackageInfo {
    std::filesystem::path Path;
    vsg::ref_ptr<vsg::Node> Root;
  };

  std::int32_t _denyCompilation{0};
  vsg::ref_ptr<vsg::Options> _options = vsg::Options::create();
  std::unordered_map<std::string, PackageInfo> _packagePreviewRoots;

  std::shared_ptr<DirectoryEntry> _dir = std::make_shared<GroupEntry>();

  void Execute(const ResetModelCommand &cmd) override;
  void OnPropertyChanged(std::shared_ptr<Entry> sender,
                         std::string_view name) override;
  void Execute(const SelectEntryCommand &cmd) override;
  void Execute(const RenameEntryCommand &cmd) override;
  void Execute(const CreateNodeCommand &cmd) override;
  void Execute(const CopyEntryCommand &cmd) override;
  void Execute(const ExportToFileCommand &cmd) override;

  // Inherited via IDataModelEditor
  void Execute(const AddLanguageCommand &cmd) override;
  void Execute(const RemoveLanguageCommand &cmd) override;
  void Execute(const RenameLanguageCommand &cmd) override;

  // Inherited via IDataModelEditor
  void Execute(const RequestSuggestedChildrenCommand &cmd) override;
  void OnSubscribed(std::shared_ptr<IDataModelObserver> observer) override;

  void Execute(const LogNotification &) override {}
  void Execute(const RefreshComplete &cmd) override;
  void Execute(const FontCompiled &cmd) override;
  void Execute(const LongOperationStarted &) override {}
  void Execute(const LongOperationEnded &) override {}
  void Execute(const SetActiveLanguageRequest &cmd) override;
};
