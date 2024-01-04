#pragma once

#include <boost/uuid/uuid.hpp>
#include <functional>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string_view>
#include <vector>

#include "EntryPath.h"
#include "EntryType.h"
#include "IEntry.h"
#include "IEntryObserver.h"
#include "Observer.h"

namespace Vandrouka {

template <typename Derived, typename... Interfaces>
class EntryBase : public ObservableBase<Derived, Interfaces...> {

  using Base = ObservableBase<Derived, Interfaces...>;

  class PropertyChangedMessage
      : public MessageBase<PropertyChangedMessage, IPropertyChangedMessage> {
  public:
    PropertyChangedMessage(EntryRef owner, std::string_view property)
        : _owner{owner}, _property{property} {}

    EntryRef GetOwner() const override { return this->_owner; }

    const std::string_view GetProperty() const override {
      return this->_property;
    }

  private:
    EntryRef _owner;
    std::string_view _property;
  };

public:
  EntryRef GetParent() const override { return this->_parent; }

  void SetParent(EntryRef parent) override {
    // do not increase references. TODO: Add weak references support.
    this->_parent = parent.Get();
  }

  EntryRef GetRoot() const override {
    Ref<IEntry> root{(IEntry *)this};
    auto next = root->GetParent();

    while (next) {
      root = next;
      next = root->GetParent();
    }

    return root;
  }

  void OnPropertyChanged(std::string_view property) {
    this->OnMessage(new PropertyChangedMessage{(IEntry *)this, property});
  }

private:
  IEntry *_parent{nullptr};
};

} // namespace Vandrouka

using ClassId = boost::uuids::uuid;
using InterfaceId = boost::uuids::uuid;

class Entry;
class IEntryObserver;
class AsyncQueue;

struct EntryProperty {
  std::string Key;
  std::string Value;
};

using EntryProperties = nlohmann::json;

class Entry;

class IEntry {
public:
  virtual std::shared_ptr<Entry> GetParent() = 0;
  virtual std::shared_ptr<Entry> GetParent() const = 0;
  virtual void SetParent(std::shared_ptr<Entry> parent) = 0;
  virtual std::shared_ptr<Entry> GetRoot() const = 0;
  virtual void AddObserver(std::shared_ptr<IEntryObserver> observer) = 0;
  virtual void RemoveObserver(std::shared_ptr<IEntryObserver> observer) = 0;
  virtual std::shared_ptr<Entry> CreateProxy(EntryPath path) = 0;
  virtual std::shared_ptr<Entry> FindEntry(const EntryPath &path) const = 0;
  virtual void Serialize(EntryProperties &properties) const = 0;
  virtual void Deserialize(const EntryProperties &properties) = 0;
  virtual void SetVisibility(bool flag) = 0;
  virtual bool GetVisibility() const = 0;
};

class Entry : protected IEntryObserver,
              public IEntry,
              public std::enable_shared_from_this<Entry> {
public:
  Entry();

  virtual ~Entry() {}

  virtual EntryType GetType() const = 0;
  std::shared_ptr<Entry> Clone();

  std::shared_ptr<Entry> GetParent() override { return _parent.lock(); }
  std::shared_ptr<Entry> GetParent() const override { return _parent.lock(); }
  virtual void SetParent(std::shared_ptr<Entry> parent) { _parent = parent; }

  std::shared_ptr<Entry> GetRoot() const;
  void AddObserver(std::shared_ptr<IEntryObserver> observer);
  void RemoveObserver(std::shared_ptr<IEntryObserver> observer);

  virtual std::shared_ptr<Entry> CreateProxy(EntryPath path) = 0;
  virtual std::shared_ptr<Entry> FindEntry(const EntryPath &path) const = 0;

  virtual void Serialize(EntryProperties &properties) const;
  void Deserialize(const EntryProperties &properties);

  virtual void SetVisibility(bool flag);
  virtual bool GetVisibility() const { return _visibility; }

protected:
  virtual std::shared_ptr<Entry>
  CreateView(std::shared_ptr<AsyncQueue> sync) = 0;

  virtual void DeserializeInternal(EntryPath path,
                                   const EntryProperties &properties);

  void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) override;
  void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) override;
  void OnPropertyChanged(std::shared_ptr<Entry> sender,
                         std::string_view name) override;
  void OnError(const LogNotification &cmd) const override;

  void CopyObserversTo(Entry &entry);
  virtual void CloneFrom(std::shared_ptr<Entry> entry);
  // Creates entry of the same type with default attributes
  virtual std::shared_ptr<Entry> CreateCopy() const = 0;

private:
  std::weak_ptr<Entry> _parent;
  std::vector<std::weak_ptr<IEntryObserver>> _observers;
  bool _visibility{true};

  friend class DirectoryEntry;
  friend class DataModel;
};

using EntryPtr = std::shared_ptr<Entry>;

class EntryView : public IEntry {
public:
};
