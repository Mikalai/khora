#pragma once

#include <magic_enum.hpp>
#include "Serializer.h"
#include "TransformEntry.h"
#include "Clone.h"

EntryType TransformEntry::GetType() const {
    return EntryType::Transform;
}

vsg::ref_ptr<vsg::MatrixTransform> TransformPackageEntry::GetTransform() const {
    return ::Clone(_transform);
}

std::shared_ptr<Entry> TransformPackageEntry::CreateProxy(EntryPath path) {
    return std::make_shared<TransformProxyEntry>(path);
}

std::shared_ptr<Entry> TransformPackageEntry::Clone() {
    return std::make_shared<TransformPackageEntry>(::Clone(_transform));
}

bool TransformPackageEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}

TransformProxyEntry::TransformProxyEntry(EntryPath path)
    : _path{ path } {
}

vsg::ref_ptr<vsg::MatrixTransform> TransformProxyEntry::GetTransform() const
{
    auto root = GetRoot();
    if (!root)
        throw std::runtime_error("Proxy transform references object in the catalog that doesn't exist.");

    if (_override) {
        vsg::ref_ptr<vsg::MatrixTransform> transform = vsg::MatrixTransform::create();
        transform->matrix = vsg::translate(_position) * vsg::rotate(_orientation) * vsg::scale(_scale);
        return transform;
    }
    else {
        if (auto entry = root->FindEntry(_path); entry) {
            if (auto transform = std::dynamic_pointer_cast<TransformEntry>(entry); transform) {
                return transform->GetTransform();
            }
            else {
                throw std::runtime_error(std::string("Proxy transform references wrong object of type ").append(magic_enum::enum_name(entry->GetType())));
            }
        }
        else {
            throw std::runtime_error("Proxy transform references object that doesn't exist.");
        }
    }
}

std::shared_ptr<Entry> TransformProxyEntry::Clone() {
    auto root = GetRoot();
    if (!root)
        throw std::runtime_error("Proxy transform references object in the catalog that doesn't exist.");

    return std::make_shared<TransformProxyEntry>(_path);
}

std::shared_ptr<Entry> TransformProxyEntry::CreateProxy(EntryPath path) {
    return std::make_shared<TransformProxyEntry>(path);
}

bool TransformProxyEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}

void TransformProxyEntry::Serialize(EntryProperties& properties) const {
    TransformEntry::Serialize(properties);

    properties["Override"] = _override;
    ::Serialize(properties["Position"], _position);
    ::Serialize(properties["Orientation"], _orientation);
    ::Serialize(properties["Scale"], _scale);
    properties["Path"] = _path.Path;
}

void TransformProxyEntry::DeserializeInternal(EntryPath path, const EntryProperties& properties) {
    TransformEntry::DeserializeInternal(path, properties);

    _override = ::Deserialize(properties, "Override", false);
    _position = ::Deserialize(properties, "Position", vsg::dvec3{});
    _orientation = ::Deserialize(properties, "Orientation", vsg::dquat{});
    _scale = ::Deserialize(properties, "Scale", vsg::dvec3{});
    _path.Path = ::Deserialize(properties, "Path", std::string{});
}
