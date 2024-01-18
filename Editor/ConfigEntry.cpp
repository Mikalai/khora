#include <magic_enum.hpp>
#include <vector>
#include <string>

#include "ConfigEntry.h"
#include "AsyncQueue.h"
#include "Clone.h"
#include "DirectoryEntry.h"
#include "Serializer.h"


namespace Vandrouka {

class ConfigEntry final : public DirectoryEntryBase<ConfigEntry, IConfigEntry> {
public:
  EntryType GetType() const override { return EntryType::Config; }

  bool GetShowTransform() const override { return _showTransform; }

  Result<bool> SetShowTransform(bool value) override {
    if (_showTransform == value)
      return false;
    _showTransform = value;
    return true;
    // OnPropertyChanged("ShowTransform");
  }

  Result<bool> AddLanguage(const std::string &value) override {
    auto it = std::find(_languages.begin(), _languages.end(), value);
    if (it != _languages.end())
      return false;

    _languages.push_back(value);
    // OnPropertyChanged("Languages");
    return true;
  }

  Result<bool> RemoveLanguage(const std::string &value) override {
    auto it = std::find(_languages.begin(), _languages.end(), value);
    if (it == _languages.end())
      return false;

    _languages.erase(it);
    // OnPropertyChanged("Languages");
    return true;
  }

  std::vector<std::string> GetLanguages() const override { return _languages; }

  std::string GetActiveLanguage() const override { return _activeLanguage; }

  Result<bool> SetActiveLanguage(const std::string &value) override {
    if (_activeLanguage == value) {
      return false;
    }

    if (auto it = std::find(_languages.begin(), _languages.end(), value);
        it == _languages.end()) {
      return {new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND, value)};
    }

    _activeLanguage = value;
    // OnPropertyChanged("ActiveLanguage");
    return true;
  }

private:
  bool _showTransform{true};
  std::vector<std::string> _languages;
  std::string _activeLanguage;
};

IReferenced *CreateConfigEntry() {
  static_assert(std::is_base_of_v<IReferenced, ConfigEntry>);
  return static_cast<IConfigEntry *>(new ConfigEntry());
}

} // namespace Vandrouka
//
// EntryType ConfigEntry::GetType() const { return EntryType::Config; }
//
// bool ConfigEntry::GetShowTransform() const { return _showTransform; }
//
// void ConfigEntry::SetShowTransform(bool value) {
//  if (_showTransform == value)
//    return;
//  _showTransform = value;
//  OnPropertyChanged(shared_from_this(), "ShowTransform");
//}
//
// bool ConfigEntry::AddLanguage(const std::string &value) {
//  auto it = std::find(_languages.begin(), _languages.end(), value);
//  if (it != _languages.end())
//    return false;
//
//  _languages.push_back(value);
//  OnPropertyChanged(shared_from_this(), "Languages");
//  return true;
//}
//
// bool ConfigEntry::RemoveLanguage(const std::string &value) {
//  auto it = std::find(_languages.begin(), _languages.end(), value);
//  if (it == _languages.end())
//    return false;
//
//  _languages.erase(it);
//  OnPropertyChanged(shared_from_this(), "Languages");
//  return true;
//}
//
// std::vector<std::string> ConfigEntry::GetLanguages() const {
//  return _languages;
//}
//
// std::string ConfigEntry::GetActiveLanguage() const { return _activeLanguage;
// }
//
// bool ConfigEntry::SetActiveLanguage(const std::string &value) {
//  if (_activeLanguage == value) {
//    return false;
//  }
//
//  if (auto it = std::find(_languages.begin(), _languages.end(), value);
//      it == _languages.end()) {
//    OnError(LogError(LOG_ENTRY_NOT_FOUND, value));
//    return false;
//  }
//
//  _activeLanguage = value;
//  OnPropertyChanged(shared_from_this(), "ActiveLanguage");
//  return true;
//}
//
// std::shared_ptr<Entry>
// ConfigEntry::CreateView(std::shared_ptr<AsyncQueue> sync) {
//  assert(std::dynamic_pointer_cast<ConfigEntry>(shared_from_this()));
//  return std::make_shared<ConfigEntryView>(
//      std::static_pointer_cast<ConfigEntry>(shared_from_this()), sync);
//}
//
// void ConfigEntry::Serialize(EntryProperties &properties) const {
//  DirectoryEntry::Serialize(properties);
//
//  properties["ShowTransform"] = _showTransform;
//
//  auto &langs = properties["Languages"];
//  for (auto &v : _languages) {
//    langs.push_back(v);
//  }
//
//  properties["ActiveLanguage"] = _activeLanguage;
//}
//
// void ConfigEntry::DeserializeInternal(EntryPath path,
//                                      const EntryProperties &properties) {
//  DirectoryEntry::DeserializeInternal(path, properties);
//
//  _showTransform = ::Deserialize(properties, "ShowTransform", true);
//  if (auto it = properties.find("Languages"); it != properties.end()) {
//    for (auto &e : *it) {
//      _languages.push_back(e.get<std::string>());
//    }
//  }
//
//  _activeLanguage = ::Deserialize(properties, "ActiveLanguage",
//  std::string{});
//}
//
// std::shared_ptr<Entry> ConfigEntry::CreateProxy(EntryPath) {
//  throw std::runtime_error("Config doesn't have proxy.");
//}
//
// bool ConfigEntry::CanAdd(std::shared_ptr<Entry>) { return true; }
//
// void ConfigEntry::CloneFrom(std::shared_ptr<Entry> entry) {
//  DirectoryEntry::CloneFrom(entry);
//  assert(std::dynamic_pointer_cast<ConfigEntry>(entry));
//  auto e = std::static_pointer_cast<ConfigEntry>(entry);
//  this->_showTransform = e->_showTransform;
//}
//
// std::shared_ptr<Entry> ConfigEntry::CreateCopy() const {
//  return std::make_shared<ConfigEntry>();
//}
//
// std::shared_ptr<Entry> ConfigEntryView::CreateProxy(EntryPath path) {
//  return _sync->Execute([&]() { return _model->CreateProxy(path); });
//}
//
// bool ConfigEntryView::CanAdd(std::shared_ptr<Entry> entry) {
//  return _sync->Execute([&]() { return _model->CanAdd(entry); });
//}
//
// void ConfigEntryView::Serialize(EntryProperties &) const {
//  throw std::runtime_error("ConfigEntryView is not serializable.");
//}
//
// void ConfigEntryView::DeserializeInternal(EntryPath, const EntryProperties &)
// {
//  throw std::runtime_error("ConfigEntryView is not deserializable.");
//}
//
// bool ConfigEntryView::GetShowTransform() const {
//  return _sync->Execute([&]() { return _model->GetShowTransform(); });
//}
//
// void ConfigEntryView::SetShowTransform(bool value) {
//  _sync->Execute([&]() { return _model->SetShowTransform(value); });
//}
//
// bool ConfigEntryView::AddLanguage(const std::string &value) {
//  return _sync->Execute([&]() { return _model->AddLanguage(value); });
//}
//
// bool ConfigEntryView::RemoveLanguage(const std::string &value) {
//  return _sync->Execute([&]() { return _model->RemoveLanguage(value); });
//}
//
// std::vector<std::string> ConfigEntryView::GetLanguages() const {
//  return _sync->Execute([&]() { return _model->GetLanguages(); });
//}
//
// std::string ConfigEntryView::GetActiveLanguage() const {
//  return _sync->Execute([&]() { return _model->GetActiveLanguage(); });
//}
//
// bool ConfigEntryView::SetActiveLanguage(const std::string &value) {
//  return _sync->Execute([&]() { return _model->SetActiveLanguage(value); });
//}
//
// void ConfigEntryView::CloneFrom(std::shared_ptr<Entry> entry) {
//  ConfigEntry::CloneFrom(entry);
//  assert(std::dynamic_pointer_cast<ConfigEntryView>(entry));
//  auto e = std::static_pointer_cast<ConfigEntryView>(entry);
//  this->_model = e->_model;
//  this->_sync = e->_sync;
//}
//
// std::shared_ptr<Entry> ConfigEntryView::CreateCopy() const {
//  return std::make_shared<ConfigEntryView>(this->_model, this->_sync);
//}
