#pragma once

#include <magic_enum.hpp>
#include "Serializer.h"
#include "GeometryEntry.h"
#include "DirectoryEntry.h"
#include "Clone.h"

EntryType GeometryEntry::GetType() const {
    return EntryType::Geometry;
}

std::shared_ptr<Entry> GeometryPackageEntry::Clone() {
    return std::make_shared<GeometryPackageEntry>(_geometry);
}

vsg::ref_ptr<vsg::VertexIndexDraw> GeometryPackageEntry::GetGeometry() {
    return ::Clone(_geometry);
}

std::shared_ptr<Entry> GeometryPackageEntry::CreateProxy(EntryPath path) {
    return std::make_shared<GeometryProxyEntry>(path);
}

std::shared_ptr<Entry> GeometryEntry::FindEntry(const EntryPath& path) const {
    return {};
}

GeometryProxyEntry::GeometryProxyEntry(EntryPath path)
    : _path{ path } {
}

std::shared_ptr<Entry> GeometryProxyEntry::Clone() {
    auto root = GetRoot();
    if (!root) {
        throw std::runtime_error("Proxy geometry references object in the catalog that doesn't exist.");
    }

    return std::make_shared<GeometryProxyEntry>(_path);
}

vsg::ref_ptr<vsg::VertexIndexDraw> GeometryProxyEntry::GetGeometry() {
    auto root = GetRoot();
    if (!root)
        throw std::runtime_error("Proxy geometry references object in the catalog that doesn't exist.");

    if (auto entry = root->FindEntry(_path); entry) {
        if (auto transform = std::dynamic_pointer_cast<GeometryEntry>(entry); transform) {
            return transform->GetGeometry();
        }
        else {
            throw std::runtime_error(std::string("Proxy geometry references wrong object of type ").append(magic_enum::enum_name(entry->GetType())));
        }
    }
    else {
        throw std::runtime_error("Proxy geometry references object that doesn't exist.");
    }
}

std::shared_ptr<Entry> GeometryProxyEntry::CreateProxy(EntryPath path) {
    return std::make_shared<GeometryProxyEntry>(path);
}

void GeometryProxyEntry::Serialize(EntryProperties& properties) const {
    GeometryEntry::Serialize(properties);
    properties["Path"] = _path.Path;
}

void GeometryProxyEntry::DeserializeInternal(EntryPath path, const EntryProperties& properties) {
    GeometryEntry::DeserializeInternal(path, properties);
    _path.Path = ::Deserialize(properties, "Path", std::string{});
}
