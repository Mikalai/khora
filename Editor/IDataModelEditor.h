#pragma once

#include <vsg/all.h>

#include <filesystem>

#include "AsyncQueue.h"
#include "EntryPath.h"
#include "IObserver.h"

class IDataModelObserver;
class Subscription;
using SubscriptionPtr = std::shared_ptr<Subscription>;

namespace Vandrouka {

class IImportFileMessage : public IMessage {
public:
  virtual const std::string &GetFilePath() const = 0;
  virtual vsg::ref_ptr<vsg::Options> GetOptions() const = 0;
  virtual const std::filesystem::path &GetProjectPath() const = 0;
};
template <> struct GetIID<IImportFileMessage> {
  static constexpr InterfaceId Id = {{0x69, 0xb7, 0xa4, 0x98, 0x79, 0x18, 0x46,
                                      0xe, 0x8c, 0xb8, 0x49, 0x6b, 0xe9, 0x2,
                                      0xaa, 0x48}};
};

class ICompileSceneMessage : public IMessage {
public:
  virtual EntryPath GetRoot() = 0;
};
template <> struct GetIID<ICompileSceneMessage> {
  static constexpr InterfaceId Id = {{0x5d, 0xc8, 0x79, 0x70, 0, 0xd0, 0x41,
                                      0x8e, 0xba, 0x9b, 0x6f, 0xb8, 0x15, 0xa4,
                                      0xe9, 0x7e}};
};

class ICopyNodeMessage : public IMessage {
public:
  virtual EntryPath GetSourcePath() const = 0;
  virtual EntryPath GetTargetPath() const = 0;
};
template <> struct GetIID<ICopyNodeMessage> {
  static constexpr InterfaceId Id = {{0xae, 0x43, 0x7f, 0xb1, 0xad, 0x35, 0x4f,
                                      0x27, 0xbd, 0x6f, 0x8b, 0xe0, 0xf2, 0xac,
                                      0x1d, 0x24}};
};

class IMoveEntryMessage : public IMessage {
public:
  virtual EntryPath GetSourcePath() const = 0;
  virtual EntryPath GetTargetPath() const = 0;
};
template <> struct GetIID<IMoveEntryMessage> {
  static constexpr InterfaceId Id = {{0xe3, 0x50, 0x76, 0xe8, 0x90, 0xeb, 0x43,
                                      0x10, 0x9b, 0xc7, 0x3a, 0xc9, 0x83, 0xaf,
                                      0xc, 0x81}};
};

class ICopyEntryMessage : public IMessage {
public:
  virtual EntryPath GetSourcePath() const = 0;
  virtual EntryPath GetTargetPath() const = 0;
};
template <> struct GetIID<ICopyEntryMessage> {
  static constexpr InterfaceId Id = {{0x2b, 0xc, 0x71, 0xc, 0xb3, 0x98, 0x4b,
                                      0x56, 0xab, 0x4a, 0xa0, 0x29, 0x4b, 0x9f,
                                      0xde, 0x1a}};
};

class IRemoveEntryMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
};
template <> struct GetIID<IRemoveEntryMessage> {
  static constexpr InterfaceId Id = {{0xa5, 0x19, 0x2d, 0x88, 0x79, 0x5c, 0x49,
                                      0x3, 0xb8, 0xaf, 0x1e, 0x88, 0x6a, 0xd6,
                                      0x5a, 0xe8}};
};

class IRenameEntryMessage : public IMessage {
public:
  virtual EntryPath GetOldPath() const = 0;
  virtual EntryPath GetNewPath() const = 0;
};
template <> struct GetIID<IRenameEntryMessage> {
  static constexpr InterfaceId Id = {{0x3e, 0x6c, 0x9, 0x9d, 0x77, 0xe, 0x4a,
                                      0x9f, 0xba, 0xd8, 0x9a, 0xde, 0xd1, 0x79,
                                      0xf4, 0x1f}};
};

class ISaveToFileMessage : public IMessage {
public:
  virtual std::filesystem::path GetPath() const = 0;
};
template <> struct GetIID<ISaveToFileMessage> {
  static constexpr InterfaceId Id = {{0xc1, 0x40, 0x53, 0xec, 0xf8, 0x61, 0x47,
                                      0x31, 0xae, 0x3e, 0xa4, 0x1, 0xee, 0xc6,
                                      0x26, 0x85}};
};

class IImportFromFileMessage : public IMessage {
public:
  virtual std::filesystem::path GetPath() const = 0;
};
template <> struct GetIID<IImportFromFileMessage> {
  static constexpr InterfaceId Id = {{0x70, 0xb0, 0x39, 0xc5, 0xd9, 0xe4, 0x46,
                                      0x4c, 0x91, 0x52, 0x17, 0x6, 0x3d, 0x25,
                                      0x42, 0xc8}};
};

class IResetModelMessage : public IMessage {};

template <> struct GetIID<IResetModelMessage> {
  static constexpr InterfaceId Id = {{0x14, 0x8, 0xab, 0x76, 0xa4, 0x53, 0x46,
                                      0x34, 0x80, 0xd1, 0xbc, 0xd, 0xf6, 0xbb,
                                      0x52, 0x83}};
};

class ISelectEntryMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
};
template <> struct GetIID<ISelectEntryMessage> {
  static constexpr InterfaceId Id = {{0x64, 0x75, 0x91, 0xe5, 0x9c, 0x70, 0x43,
                                      0xb3, 0xbb, 0xa6, 0x1, 0x5c, 0x24, 0x6c,
                                      0xe0, 0x49}};
};

class ICreateNodeMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
  virtual std::string GetType() const = 0;
};
template <> struct GetIID<ICreateNodeMessage> {
  static constexpr InterfaceId Id = {{0xc9, 0x40, 0x9d, 0xba, 0x9c, 0x9c, 0x41,
                                      0x8c, 0x8e, 0xe4, 0x9b, 0xa5, 0x56, 0x8d,
                                      0xa1, 0xd3}};
};

class IExportToFileMessage : public IMessage {
public:
  virtual std::string GetPath() const = 0;
};
template <> struct GetIID<IExportToFileMessage> {
  static constexpr InterfaceId Id = {{0xb8, 0xe8, 0x64, 0xbc, 0x4, 0xda, 0x45,
                                      0xdb, 0xb5, 0x8c, 0x12, 0xd3, 0xe7, 0xc4,
                                      0x2a, 0x27}};
};

class IAddLanguageMessage : public IMessage {
public:
  virtual std::string GetValue() = 0;
};
template <> struct GetIID<IAddLanguageMessage> {
  static constexpr InterfaceId Id = {{0x47, 0x1e, 0x73, 0x3, 0xeb, 0xeb, 0x48,
                                      0x2, 0x81, 0xe0, 0xb0, 0x8, 0x41, 0x51,
                                      0xc7, 0xea}};
};

class IRemoveLanguageMessage : public IMessage {
public:
  virtual std::string GetValue() = 0;
};
template <> struct GetIID<IRemoveLanguageMessage> {
  static constexpr InterfaceId Id = {{0x9b, 0xc2, 0xa2, 0x55, 0x5c, 0xb1, 0x4c,
                                      0x4e, 0xbd, 0xb7, 0xa, 0x1f, 0xd9, 0x26,
                                      0xed, 0x15}};
};

class IRenameLanguageMessage : public IMessage {
public:
  virtual std::string GetOldValue() = 0;
  virtual std::string GetNewValue() = 0;
};
template <> struct GetIID<IRenameLanguageMessage> {
  static constexpr InterfaceId Id = {{0x54, 0xe1, 0xa1, 0xe3, 0xb0, 0xbf, 0x48,
                                      0x49, 0xac, 0x57, 0xf7, 0x6, 0x60, 0x30,
                                      0x9e, 0xa4}};
};

class IRequestSuggestedChildrenMessage : public IMessage {
public:
  virtual const EntryPath &GetPath() const = 0;
  virtual const std::string &GetContext() const = 0;
};
template <> struct GetIID<IRequestSuggestedChildrenMessage> {
  static constexpr InterfaceId Id = {{0x93, 0x32, 0xee, 0x1c, 0xd1, 0x1a, 0x4b,
                                      0x40, 0x8f, 0x82, 0x30, 0xa8, 0x40, 0xe9,
                                      0x86, 0xd1}};
};

class ISetActiveLanguageMessage : public IMessage {
public:
  virtual const std::string &GetLanguage() const = 0;
};
template <> struct GetIID<ISetActiveLanguageMessage> {
  static constexpr InterfaceId Id = {{0x46, 0x38, 0xdb, 0x7b, 0x2b, 0x62, 0x48,
                                      0xc8, 0xbf, 0xad, 0x9a, 0xfe, 0xd3, 0x10,
                                      0x62, 0xb2}};
};

} // namespace Vandrouka

class IDataModelEditor {
public:
  virtual ~IDataModelEditor();

  struct ImportFileCommand {
    std::string FilePath;
    vsg::ref_ptr<vsg::Options> Options;
    std::filesystem::path ProjectPath;
  };

  virtual void Execute(const ImportFileCommand &cmd) = 0;

  struct CompileSceneCommand {
    EntryPath Root;
  };

  virtual void Execute(const CompileSceneCommand &cmd) = 0;

  struct CopyNodeCommand {
    EntryPath SourcePath;
    EntryPath TargetPath;
  };

  virtual void Execute(const CopyNodeCommand &cmd) = 0;

  struct MoveEntryCommand {
    EntryPath SourcePath;
    EntryPath TargetPath;
  };

  virtual void Execute(const MoveEntryCommand &cmd) = 0;

  struct CopyEntryCommand {
    EntryPath SourcePath;
    EntryPath TargetPath;
  };

  virtual void Execute(const CopyEntryCommand &cmd) = 0;

  struct RemoveEntryCommand {
    EntryPath Path;
  };

  virtual void Execute(const RemoveEntryCommand &cmd) = 0;

  struct RenameEntryCommand {
    EntryPath OldPath;
    EntryPath NewPath;
  };

  virtual void Execute(const RenameEntryCommand &cmd) = 0;

  struct SaveToFileCommand {
    std::filesystem::path Path;
  };

  virtual void Execute(const SaveToFileCommand &cmd) = 0;

  struct ImportFromFileCommand {
    std::filesystem::path Path;
  };

  virtual void Execute(const ImportFromFileCommand &cmd) = 0;

  struct ResetModelCommand {};

  virtual void Execute(const ResetModelCommand &cmd) = 0;

  [[nodiscard]] virtual SubscriptionPtr
  Subscribe(std::shared_ptr<IDataModelObserver> observer) = 0;

  struct SelectEntryCommand {
    EntryPath Path;
  };

  virtual void Execute(const SelectEntryCommand &cmd) = 0;

  virtual std::shared_ptr<AsyncQueue> GetSyncContext() = 0;

  struct CreateNodeCommand {
    EntryPath Path;
    std::string Type;
  };

  virtual void Execute(const CreateNodeCommand &cmd) = 0;

  struct ExportToFileCommand {
    std::string Path;
  };

  virtual void Execute(const ExportToFileCommand &cmd) = 0;

  struct AddLanguageCommand {
    std::string Value;
  };

  virtual void Execute(const AddLanguageCommand &cmd) = 0;

  struct RemoveLanguageCommand {
    std::string Value;
  };

  virtual void Execute(const RemoveLanguageCommand &cmd) = 0;

  struct RenameLanguageCommand {
    std::string OldValue;
    std::string NewValue;
  };

  virtual void Execute(const RenameLanguageCommand &cmd) = 0;

  struct RequestSuggestedChildrenCommand {
    EntryPath Path;
    std::string Context;
  };

  virtual void Execute(const RequestSuggestedChildrenCommand &cmd) = 0;

  struct SetActiveLanguageRequest {
    std::string Language;
  };

  virtual void Execute(const SetActiveLanguageRequest &cmd) = 0;
};
