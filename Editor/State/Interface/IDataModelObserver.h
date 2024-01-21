#pragma once

#include <vsg/all.h>

#include "EntryPath.h"
#include "EntryType.h"
#include <Fundamental/IError.h>
#include <Fundamental/IAsyncQueue.h>
#include "IConfigEntry.h"
#include "IEntry.h"
#include <Fundamental/Interface/IObserver.h>

namespace Vandrouka {



//class IItemAddedMessage : public IMessage {
//public:
//  virtual EntryPath GetPath() const = 0;
//  virtual EntryType GetType() const = 0;
//};
//
//template <> struct GetIID<IItemAddedMessage> {
//  static constexpr InterfaceId Id = {{0x11, 0xfc, 0x50, 0xb8, 0xd1, 0xac, 0x45,
//                                      0xa8, 0xaf, 0x65, 0x51, 0x22, 0x27, 0xe,
//                                      0xa6, 0xf6}};
//};
//
//class IItemRemovedMessage : public IMessage {
//public:
//  virtual EntryPath GetPath() const = 0;
//  virtual EntryType GetType() const = 0;
//};
//template <> struct GetIID<IItemRemovedMessage> {
//  static constexpr InterfaceId Id = {{0x14, 0x5e, 0x3, 0x2b, 0x1b, 0xe5, 0x44,
//                                      0xa7, 0x9c, 0x84, 0x1e, 0x35, 0x86, 0,
//                                      0xc9, 0x4a}};
//};



} // namespace Vandrouka

//class Entry;
//class ConfigEntry;
//
//class IDataModelObserver {
//public:
//  virtual ~IDataModelObserver();
//
//  struct CompileCommand {
//    vsg::ref_ptr<vsg::Node> Object;
//    std::function<void(vsg::ref_ptr<vsg::Node>, vsg::CompileResult &)>
//        OnComplete;
//  };
//
//  virtual void Execute(const CompileCommand &cmd) = 0;
//
//  struct ItemAddedNotification {
//    EntryPath Path;
//    EntryType Type;
//    bool Visibility;
//  };
//
//  virtual void Execute(const ItemAddedNotification &cmd) = 0;
//
//  struct ItemRemovedNotification {
//    EntryPath Path;
//    EntryType Type;
//  };
//
//  virtual void Execute(const ItemRemovedNotification &cmd) = 0;
//
//  struct SceneCompeledNotification {
//    vsg::ref_ptr<vsg::Node> Root;
//  };
//
//  virtual void Execute(const SceneCompeledNotification &cmd) = 0;
//
//  struct ModelResetNotification {};
//
//  virtual void Execute(const ModelResetNotification &cmd) = 0;
//
//  virtual void Execute(const LogNotification &cmd) = 0;
//
//  struct EntrySelectedNotification {
//    std::shared_ptr<Entry> SelectedEntry;
//  };
//
//  virtual void Execute(const EntrySelectedNotification &cmd) = 0;
//
//  struct EntryPropertyChangedNotification {
//    std::shared_ptr<Entry> ChangedEntry;
//    std::string_view Property;
//  };
//
//  virtual void Execute(const EntryPropertyChangedNotification &cmd) = 0;
//
//  struct ConfigNotification {
//    std::shared_ptr<ConfigEntry> Config;
//  };
//
//  virtual void Execute(const ConfigNotification &cmd) = 0;
//
//  struct LanguageAddedNotification {
//    std::string Value;
//  };
//
//  virtual void Execute(const LanguageAddedNotification &cmd) = 0;
//
//  struct LanguageRemoveNotification {
//    std::string Value;
//  };
//
//  virtual void Execute(const LanguageRemoveNotification &cmd) = 0;
//
//  struct SuggestedChildrenNotification {
//    struct Suggestion {
//      std::string Type;
//      std::string Name;
//    };
//    std::string Context;
//    EntryPath Path;
//    std::vector<Suggestion> Suggestions;
//  };
//
//  virtual void Execute(const SuggestedChildrenNotification &cmd) = 0;
//
//  struct BulkOperationStartedNotification {};
//
//  virtual void Execute(const BulkOperationStartedNotification &cmd) = 0;
//
//  struct BulkOperationEndedNotification {};
//
//  virtual void Execute(const BulkOperationEndedNotification &cmd) = 0;
//
//  struct ActiveLanguageChanged {
//    std::string OldLanguage;
//    std::string NewLanguage;
//  };
//
//  virtual void Execute(const ActiveLanguageChanged &cmd) = 0;
//};
//
//class DataModelObserverAdapter : public IDataModelObserver {
//public:
//  DataModelObserverAdapter(IDataModelObserver &other) : _other{other} {}
//
//  void Execute(const CompileCommand &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const ItemAddedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const ItemRemovedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const SceneCompeledNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const ModelResetNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const LogNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const EntrySelectedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const EntryPropertyChangedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const ConfigNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const LanguageAddedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const LanguageRemoveNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const SuggestedChildrenNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const BulkOperationStartedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const BulkOperationEndedNotification &cmd) override {
//    this->_other.Execute(cmd);
//  }
//  void Execute(const ActiveLanguageChanged &cmd) override {
//    this->_other.Execute(cmd);
//  }
//
//private:
//  IDataModelObserver &_other;
//};
