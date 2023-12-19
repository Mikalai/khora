#pragma once

#include <magic_enum.hpp>
#include "Serializer.h"
#include "AsyncQueue.h"
#include "ConfigEntry.h"
#include "Clone.h"

EntryType ConfigEntry::GetType() const {
    return EntryType::Config;
}

bool ConfigEntry::GetShowTransform() const {
    return _showTransform;
}

void ConfigEntry::SetShowTransform(bool value)
{
    if (_showTransform == value)
        return;
    _showTransform = value;
    OnPropertyChanged(shared_from_this(), "ShowTransform");
}

std::shared_ptr<Entry> ConfigEntry::CreateView(std::shared_ptr<AsyncQueue> sync) {
    assert(std::dynamic_pointer_cast<ConfigEntry>(shared_from_this()));
    return std::make_shared<ConfigEntryView>(std::static_pointer_cast<ConfigEntry>(shared_from_this()), sync);
}

void ConfigEntry::Serialize(EntryProperties& properties) const {
    DirectoryEntry::Serialize(properties);

    properties["ShowTransform"] = _showTransform;
}

void ConfigEntry::DeserializeInternal(EntryPath path, const EntryProperties& properties) {
    DirectoryEntry::DeserializeInternal(path, properties);

    _showTransform = ::Deserialize(properties, "ShowTransform", true);
}

std::shared_ptr<Entry> ConfigEntry::CreateProxy(EntryPath path) {
    throw std::runtime_error("Config doesn't have proxy.");
}

bool ConfigEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}

void ConfigEntry::CloneFrom(std::shared_ptr<Entry> entry) {
    DirectoryEntry::CloneFrom(entry);
    assert(std::dynamic_pointer_cast<ConfigEntry>(entry));
    auto e = std::static_pointer_cast<ConfigEntry>(entry);
    this->_showTransform = e->_showTransform;
}

std::shared_ptr<Entry> ConfigEntry::CreateCopy() const {
    return std::make_shared<ConfigEntry>();
}

std::shared_ptr<Entry> ConfigEntryView::CreateProxy(EntryPath path) {
    return _sync->Execute([&]() { return _model->CreateProxy(path); });
}

bool ConfigEntryView::CanAdd(std::shared_ptr<Entry> entry) {
    return _sync->Execute([&]() { return _model->CanAdd(entry); });
}

void ConfigEntryView::Serialize(EntryProperties& properties) const {
    throw std::runtime_error("ConfigEntryView is not serializable.");
}

void ConfigEntryView::DeserializeInternal(EntryPath path, const EntryProperties& properties) {
    throw std::runtime_error("ConfigEntryView is not deserializable.");
}

bool ConfigEntryView::GetShowTransform() const {
    return _sync->Execute([&]() { return _model->GetShowTransform(); });
}

void ConfigEntryView::SetShowTransform(bool value) {
    _sync->Execute([&]() { return _model->SetShowTransform(value); });
}

void ConfigEntryView::CloneFrom(std::shared_ptr<Entry> entry) {
    ConfigEntry::CloneFrom(entry);
    assert(std::dynamic_pointer_cast<ConfigEntryView>(entry));
    auto e = std::static_pointer_cast<ConfigEntryView>(entry);
    this->_model = e->_model;
    this->_sync = e->_sync;
}

std::shared_ptr<Entry> ConfigEntryView::CreateCopy() const {
    return std::make_shared<ConfigEntryView>(this->_model, this->_sync);
}
