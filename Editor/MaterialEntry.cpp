#pragma once

#include <magic_enum.hpp>
#include "MaterialEntry.h"
#include "Clone.h"

EntryType MaterialEntry::GetType() const {
    return EntryType::Material;
}

std::shared_ptr<Entry> MaterialPackageEntry::Clone() {
    return std::make_shared<MaterialPackageEntry>(::Clone(_state));
}

vsg::ref_ptr<vsg::StateGroup> MaterialPackageEntry::GetState() const {
    return ::Clone(_state);
}

bool MaterialPackageEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}

std::shared_ptr<Entry> MaterialPackageEntry::CreateProxy(std::shared_ptr<Entry> root, EntryPath path) {
    return std::make_shared<MaterialProxyEntry>(path, root);
}

MaterialProxyEntry::MaterialProxyEntry(EntryPath path, std::shared_ptr<Entry> root)
    : _path{ path }
    , _root{ root } {
}

vsg::ref_ptr<vsg::StateGroup> MaterialProxyEntry::GetState() const {
    auto root = _root.lock();
    if (!root)
        throw std::runtime_error("Proxy material references object in the catalog that doesn't exist.");

    if (auto entry = root->FindEntry(_path); entry) {
        if (auto transform = std::dynamic_pointer_cast<MaterialEntry>(entry); transform) {
            return transform->GetState();
        }
        else {
            throw std::runtime_error(std::string("Proxy material references wrong object of type ").append(magic_enum::enum_name(entry->GetType())));
        }
    }
    else {
        throw std::runtime_error("Proxy material references object that doesn't exist.");
    }
}

std::shared_ptr<Entry> MaterialProxyEntry::Clone() {
    auto root = _root.lock();
    
    if (!root) {
        throw std::runtime_error("Material proxy can't be cloned because catalog is not valid.");
    }

    return std::make_shared<MaterialProxyEntry>(_path, root);
}

std::shared_ptr<Entry> MaterialProxyEntry::CreateProxy(std::shared_ptr<Entry> root, EntryPath path) {
    return std::make_shared<MaterialProxyEntry>(_path, root);
}

bool MaterialProxyEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}

void MaterialProxyEntry::Serialize(EntryProperties& properties) const {
    MaterialEntry::Serialize(properties);
    properties["Path"] = _path.Path;
}

void MaterialProxyEntry::Deserialize(const EntryProperties& properties) {
    MaterialEntry::Deserialize(properties);
    _path.Path = properties["Path"].get<std::string>();
}

