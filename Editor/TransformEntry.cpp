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

std::shared_ptr<Entry> TransformPackageEntry::CreateProxy(std::shared_ptr<Entry> root, EntryPath path) {
    return std::make_shared<TransformProxyEntry>(path, root);
}

std::shared_ptr<Entry> TransformPackageEntry::Clone() {
    return std::make_shared<TransformPackageEntry>(::Clone(_transform));
}

bool TransformPackageEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}

TransformProxyEntry::TransformProxyEntry(EntryPath path, std::shared_ptr<Entry> root)
    : _path{ path }
    , _root{ root } {
}

vsg::ref_ptr<vsg::MatrixTransform> TransformProxyEntry::GetTransform() const
{
    auto root = _root.lock();
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
    auto root = _root.lock();
    if (!root)
        throw std::runtime_error("Proxy transform references object in the catalog that doesn't exist.");

    return std::make_shared<TransformProxyEntry>(_path, root);
}

std::shared_ptr<Entry> TransformProxyEntry::CreateProxy(std::shared_ptr<Entry> root, EntryPath path) {
    return std::make_shared<TransformProxyEntry>(path, root);
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

void TransformProxyEntry::Deserialize(const EntryProperties& properties) {
    TransformEntry::Deserialize(properties);
}
