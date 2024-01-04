#include "Entry.h"

#include "Serializer.h"
#include <magic_enum.hpp>

Entry::Entry() {}

std::shared_ptr<Entry> Entry::Clone() {
  auto copy = CreateCopy();
  copy->CloneFrom(shared_from_this());
  return copy;
}

std::shared_ptr<Entry> Entry::GetRoot() const {
  auto root = const_cast<Entry &>(*this).shared_from_this();
  auto next = root->GetParent();

  while (next) {
    root = next;
    next = root->GetParent();
  }

  return root;
}

void Entry::AddObserver(std::shared_ptr<IEntryObserver> observer) {
  _observers.push_back(observer);
}

void Entry::RemoveObserver(std::shared_ptr<IEntryObserver> observer) {
  auto it = std::find_if(_observers.begin(), _observers.end(),
                         [=](auto v) { return v.lock() == observer; });

  if (it == _observers.end())
    return;

  _observers.erase(it);
}

void Entry::Serialize(EntryProperties &properties) const {
  properties["Type"] = magic_enum::enum_name(GetType());
  if (!_visibility)
    properties["Visibility"] = _visibility;
}

void Entry::Deserialize(const EntryProperties &properties) {
  DeserializeInternal({}, properties);
  _visibility = ::Deserialize(properties, "Visibility", true);
}

void Entry::DeserializeInternal(EntryPath, const EntryProperties &) {}

void Entry::OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) {
  std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
    if (auto p = v.lock(); p) {
      p->OnEntryAdded(path, entry);
    }
  });
}

void Entry::OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) {
  std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
    if (auto p = v.lock(); p) {
      p->OnEntryRemoved(path, entry);
    }
  });
}

void Entry::OnPropertyChanged(std::shared_ptr<Entry> sender,
                              std::string_view name) {
  std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
    if (auto p = v.lock(); p) {
      p->OnPropertyChanged(sender, name);
    }
  });
}

void Entry::OnError(const LogNotification &cmd) const {
  std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
    if (auto p = v.lock(); p) {
      p->OnError(cmd);
    }
  });
}

void Entry::CopyObserversTo(Entry &entry) {
  std::vector<std::weak_ptr<IEntryObserver>> myObserver;
  { myObserver = _observers; }
  { entry._observers = myObserver; }
}

void Entry::CloneFrom(std::shared_ptr<Entry> entry) {
  _observers = entry->_observers;
  _parent = entry->_parent;
}

void Entry::SetVisibility(bool flag) {
  if (_visibility == flag)
    return;
  _visibility = flag;
  OnPropertyChanged(shared_from_this(), "Visibility");
}
