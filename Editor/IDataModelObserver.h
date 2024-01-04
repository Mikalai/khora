#pragma once

#include <vsg/all.h>

#include "EntryPath.h"
#include "EntryType.h"
#include "Errors.h"
#include "IAsyncQueue.h"
#include "IConfigEntry.h"
#include "IEntry.h"
#include "IObserver.h"

namespace Vandrouka {

class ICompileMessage : public IMessage {
public:
  virtual vsg::ref_ptr<vsg::Node> GetObject() = 0;
  virtual Ref<IAsyncTask> GetCompletion() = 0;
  // std::function<void(vsg::ref_ptr<vsg::Node>, vsg::CompileResult &)>
  //     OnComplete;
};
template <> struct GetIID<ICompileMessage> {
  static constexpr InterfaceId Id = {{0xb1, 0x8c, 0x43, 0x13, 0xe6, 0xdb, 0x47,
                                      0x5, 0x8f, 0x2a, 0x6f, 0x6e, 0x6f, 0x85,
                                      0x7e, 0x94}};
};

class IItemAddedMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
  virtual EntryType GetType() const = 0;
  virtual bool GetVisibility() const = 0;
};
template <> struct GetIID<IItemAddedMessage> {
  static constexpr InterfaceId Id = {{0x11, 0xfc, 0x50, 0xb8, 0xd1, 0xac, 0x45,
                                      0xa8, 0xaf, 0x65, 0x51, 0x22, 0x27, 0xe,
                                      0xa6, 0xf6}};
};

class IItemRemovedMessage : public IMessage {
public:
  virtual EntryPath GetPath() const = 0;
  virtual EntryType GetType() const = 0;
};
template <> struct GetIID<IItemRemovedMessage> {
  static constexpr InterfaceId Id = {{0x14, 0x5e, 0x3, 0x2b, 0x1b, 0xe5, 0x44,
                                      0xa7, 0x9c, 0x84, 0x1e, 0x35, 0x86, 0,
                                      0xc9, 0x4a}};
};

class ISceneCompeledMessage : public IMessage {
public:
  virtual vsg::ref_ptr<vsg::Node> GetRoot() const = 0;
};
template <> struct GetIID<ISceneCompeledMessage> {
  static constexpr InterfaceId Id = {{0xa2, 0xd4, 0xa1, 0x7, 0x95, 0xbe, 0x41,
                                      0x34, 0xb3, 0x79, 0x7b, 0x77, 0x62, 0xef,
                                      0xeb, 0xd9}};
};

class IModelResetMessage : public IMessage {};
template <> struct GetIID<IModelResetMessage> {
  static constexpr InterfaceId Id = {{0x93, 0xaf, 0x47, 0xb9, 0xf2, 0x54, 0x44,
                                      0xcc, 0x85, 0x3b, 0xd1, 0x2f, 0x25, 0x3d,
                                      0xf7, 0x4b}};
};

class IEntrySelectedMessage : public IMessage {
public:
  virtual EntryRef GetSelectedEntry() = 0;
};

template <> struct GetIID<IEntrySelectedMessage> {
  static constexpr InterfaceId Id = {{0x9a, 0xc9, 0xf8, 0x28, 0x13, 0x67, 0x40,
                                      0xa, 0xba, 0xc, 0x4f, 0x2d, 0xcb, 0xce,
                                      0xc4, 0x4f}};
};

class IEntryPropertyChangedMessage : public IMessage {
  EntryRef ChangedEntry;
  std::string_view Property;
};
template <> struct GetIID<IEntryPropertyChangedMessage> {
  static constexpr InterfaceId Id = {{0xd0, 0xd, 0x7a, 0x58, 0x8d, 0xb8, 0x4a,
                                      0x35, 0xa2, 0x3f, 0x89, 0x2b, 0x1d, 0xb9,
                                      0x57, 0x1a}};
};

class IConfigChangedMessage : public IMessage {
public:
  virtual Ref<IConfigEntry> GetConfig() const = 0;
};

template <> struct GetIID<IConfigChangedMessage> {
  static constexpr InterfaceId Id = {{0x1, 0xe7, 0x7c, 0xf, 0xb5, 0x91, 0x4f,
                                      0x5c, 0x9b, 0x78, 0x88, 0xb, 0x4d, 0xa5,
                                      0xde, 0x56}};
};

class ILanguageAddedMessage : public IMessage {
public:
  virtual const std::string &GetValue() const = 0;
};
template <> struct GetIID<ILanguageAddedMessage> {
  static constexpr InterfaceId Id = {{0x67, 0x41, 0x4b, 0x9f, 0x40, 0xdb, 0x49,
                                      0x30, 0xb7, 0xf5, 0xf8, 0x18, 0x2f, 0xb6,
                                      0x4b, 0x9c}};
};

class ILanguageRemovedMessage : public IMessage {
public:
  virtual const std::string &GetValue() const = 0;
};

template <> struct GetIID<ILanguageRemovedMessage> {
  static constexpr InterfaceId Id = {{0xf0, 0xcc, 0xb0, 0xc, 0x6c, 0x9e, 0x41,
                                      0x63, 0x9f, 0x90, 0xd9, 0x12, 0x68, 0xe1,
                                      0x46, 0x88}};
};

class ISuggestedChildrenMessage : public IMessage {
public:
  struct Suggestion {
    std::string Type;
    std::string Name;
  };

  virtual const std::string &GetContext() const = 0;
  ;
  virtual const EntryPath &GetPath() const = 0;
  virtual const std::vector<Suggestion> &GetSuggestions() const = 0;
};

template <> struct GetIID<ISuggestedChildrenMessage> {
  static constexpr InterfaceId Id = {{0x2f, 0x1e, 0x9e, 0xec, 0x7a, 0x18, 0x40,
                                      0x10, 0x8a, 0x45, 0x49, 0xd8, 0x9f, 0x8d,
                                      0xf2, 0xe4}};
};

class IBulkOperationStartedMessage : public IMessage {};
template <> struct GetIID<IBulkOperationStartedMessage> {
  static constexpr InterfaceId Id = {{0xce, 0x4, 0x16, 0xe, 0x82, 0xe6, 0x48,
                                      0xd1, 0x99, 0x2c, 0xb8, 0xb5, 0x51, 0x63,
                                      0x4d, 0x72}};
};

class IBulkOperationEndedMessage : public IMessage {};
template <> struct GetIID<IBulkOperationEndedMessage> {
  static constexpr InterfaceId Id = {{0xc2, 0x57, 0x31, 0x62, 0x9c, 0xca, 0x41,
                                      0xab, 0xbc, 0xf4, 0x7, 0xee, 0xf0, 0x9e,
                                      0x3, 0x2f}};
};

class IActiveLanguageChangedMessage : public IMessage {
public:
  virtual const std::string &GetOldLanguage() const;
  virtual const std::string &GetNewLanguage() const;
};
template <> struct GetIID<IActiveLanguageChangedMessage> {
  static constexpr InterfaceId Id = {{0xd0, 0x77, 0x6e, 0x7e, 0x3c, 0x1d, 0x4d,
                                      0x73, 0xac, 0x14, 0x3d, 0xf0, 0x23, 0xfc,
                                      0x35, 0xb8}};
};
} // namespace Vandrouka

class Entry;
class ConfigEntry;

class IDataModelObserver {
public:
  virtual ~IDataModelObserver();

  struct CompileCommand {
    vsg::ref_ptr<vsg::Node> Object;
    std::function<void(vsg::ref_ptr<vsg::Node>, vsg::CompileResult &)>
        OnComplete;
  };

  virtual void Execute(const CompileCommand &cmd) = 0;

  struct ItemAddedNotification {
    EntryPath Path;
    EntryType Type;
    bool Visibility;
  };

  virtual void Execute(const ItemAddedNotification &cmd) = 0;

  struct ItemRemovedNotification {
    EntryPath Path;
    EntryType Type;
  };

  virtual void Execute(const ItemRemovedNotification &cmd) = 0;

  struct SceneCompeledNotification {
    vsg::ref_ptr<vsg::Node> Root;
  };

  virtual void Execute(const SceneCompeledNotification &cmd) = 0;

  struct ModelResetNotification {};

  virtual void Execute(const ModelResetNotification &cmd) = 0;

  virtual void Execute(const LogNotification &cmd) = 0;

  struct EntrySelectedNotification {
    std::shared_ptr<Entry> SelectedEntry;
  };

  virtual void Execute(const EntrySelectedNotification &cmd) = 0;

  struct EntryPropertyChangedNotification {
    std::shared_ptr<Entry> ChangedEntry;
    std::string_view Property;
  };

  virtual void Execute(const EntryPropertyChangedNotification &cmd) = 0;

  struct ConfigNotification {
    std::shared_ptr<ConfigEntry> Config;
  };

  virtual void Execute(const ConfigNotification &cmd) = 0;

  struct LanguageAddedNotification {
    std::string Value;
  };

  virtual void Execute(const LanguageAddedNotification &cmd) = 0;

  struct LanguageRemoveNotification {
    std::string Value;
  };

  virtual void Execute(const LanguageRemoveNotification &cmd) = 0;

  struct SuggestedChildrenNotification {
    struct Suggestion {
      std::string Type;
      std::string Name;
    };
    std::string Context;
    EntryPath Path;
    std::vector<Suggestion> Suggestions;
  };

  virtual void Execute(const SuggestedChildrenNotification &cmd) = 0;

  struct BulkOperationStartedNotification {};

  virtual void Execute(const BulkOperationStartedNotification &cmd) = 0;

  struct BulkOperationEndedNotification {};

  virtual void Execute(const BulkOperationEndedNotification &cmd) = 0;

  struct ActiveLanguageChanged {
    std::string OldLanguage;
    std::string NewLanguage;
  };

  virtual void Execute(const ActiveLanguageChanged &cmd) = 0;
};

class DataModelObserverAdapter : public IDataModelObserver {
public:
  DataModelObserverAdapter(IDataModelObserver &other) : _other{other} {}

  void Execute(const CompileCommand &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const ItemAddedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const ItemRemovedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const SceneCompeledNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const ModelResetNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const LogNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const EntrySelectedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const EntryPropertyChangedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const ConfigNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const LanguageAddedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const LanguageRemoveNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const SuggestedChildrenNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const BulkOperationStartedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const BulkOperationEndedNotification &cmd) override {
    this->_other.Execute(cmd);
  }
  void Execute(const ActiveLanguageChanged &cmd) override {
    this->_other.Execute(cmd);
  }

private:
  IDataModelObserver &_other;
};
