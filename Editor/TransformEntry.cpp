#pragma once

#include <magic_enum.hpp>
#include "Serializer.h"
#include "AsyncQueue.h"
#include "TransformEntry.h"
#include "Clone.h"
#include "Errors.h"

TransformEntry::TransformEntry()
{
}

TransformEntry::TransformEntry(const TransformEntry& entry)
    : DirectoryEntry{entry}
{
}

vsg::dmat4 TransformEntry::GetWorldMatrix() {
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> path;
    path.push_back(GetTransform());
    auto parent = GetParent();

    while (parent) {
        if (auto tr = std::dynamic_pointer_cast<TransformEntry>(parent); tr) {
            path.push_back(tr->GetTransform());
        }
        parent = parent->GetParent();
    }

    vsg::dmat4 r;

    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        r = r * (*it)->matrix;
    }

    return r;
}

EntryType TransformEntry::GetType() const {
    return EntryType::Transform;
}

std::shared_ptr<Entry> TransformEntry::CreateView(std::shared_ptr<AsyncQueue> sync) {
    assert(std::dynamic_pointer_cast<TransformEntry>(shared_from_this()));
    return std::make_shared<TransformEntryView>(std::static_pointer_cast<TransformEntry>(shared_from_this()), sync);
}

vsg::ref_ptr<vsg::MatrixTransform> TransformPackageEntry::GetTransform() const {
    return ::Clone(_transform);
}

std::shared_ptr<Entry> TransformPackageEntry::CreateProxy(EntryPath path) {
    return std::make_shared<TransformProxyEntry>(path);
}

std::shared_ptr<Entry> TransformPackageEntry::CreateCopy() const {
    return std::make_shared<TransformPackageEntry>();
}

void TransformPackageEntry::CloneFrom(std::shared_ptr<Entry> entry) {
    
    TransformEntry::CloneFrom(entry);

    assert(std::dynamic_pointer_cast<TransformPackageEntry>(entry));
    auto e = std::static_pointer_cast<TransformPackageEntry>(entry);

    this->_transform = e->_transform;
}

TransformProxyEntry::TransformProxyEntry(EntryPath path)
    : _path{ path } {
}

vsg::ref_ptr<vsg::MatrixTransform> TransformProxyEntry::GetTransform() const
{
    auto root = GetRoot();
    if (!root)
        throw std::runtime_error("Proxy transform references object in the catalog that doesn't exist.");

    if (_override || !_path.IsValid()) {
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
                const_cast<TransformProxyEntry&>(*this).OnError(LogError(LOG_TYPE_MISMATCH));
                return {};                
            }
        }
        else {
            const_cast<TransformProxyEntry&>(*this).OnError(LogError(LOG_ENTRY_NOT_FOUND, this->_path.Path));
            return {};
        }
    }
}

void TransformProxyEntry::SetOverride(bool flag) {
    if (_override == flag)
        return;

    _override = flag;
    OnPropertyChanged(shared_from_this(), "Override");
}

void TransformProxyEntry::SetPosition(vsg::dvec3 value) {
    if (_position == value)
        return;

    _position = value;
    OnPropertyChanged(shared_from_this(), "Position");
}

void TransformProxyEntry::SetScale(vsg::dvec3 value) { 
    if (_scale == value)
        return;

    _scale = value; 
    OnPropertyChanged(shared_from_this(), "Scale");
}

void TransformProxyEntry::SetOrientation(vsg::dquat value) { 
    if (_orientation == value)
        return;

    _orientation = value; 
    OnPropertyChanged(shared_from_this(), "Orientation");
}

std::shared_ptr<Entry> TransformProxyEntry::CreateProxy(EntryPath path) {
    return std::make_shared<TransformProxyEntry>(path);
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

void TransformProxyEntry::CloneFrom(std::shared_ptr<Entry> entry)
{
    TransformEntry::CloneFrom(entry);
    assert(std::dynamic_pointer_cast<TransformProxyEntry>(entry));

    auto e = std::static_pointer_cast<TransformProxyEntry>(entry);

    this->_orientation = e->_orientation;
    this->_override = e->_override;
    this->_path = e->_path;
    this->_position = e->_position;
    this->_scale = e->_scale;
}

std::shared_ptr<Entry> TransformProxyEntry::CreateCopy() const {
    return std::make_shared<TransformProxyEntry>();
}

std::shared_ptr<Entry> TransformEntryView::CreateProxy(EntryPath path) {
    return _sync->Execute([&]() { return _model->CreateProxy(path); });
}

vsg::ref_ptr<vsg::MatrixTransform> TransformEntryView::GetTransform() const {
    return _sync->Execute([&]() { return _model->GetTransform(); });
}

void TransformEntryView::SetOverride(bool flag) {
    _sync->Execute([&]() { return _model->SetOverride(flag); });
}

bool TransformEntryView::GetOverride() const {
    return _sync->Execute([&]() { return _model->GetOverride(); });
}

void TransformEntryView::SetPosition(vsg::dvec3 value) {
    _sync->Execute([&]() { return _model->SetPosition(value); });
}

vsg::dvec3 TransformEntryView::GetPosition() const {
    return _sync->Execute([&]() { return _model->GetPosition(); });
}

void TransformEntryView::SetScale(vsg::dvec3 value) {
    _sync->Execute([&]() { return _model->SetScale(value); });
}

vsg::dvec3 TransformEntryView::GetScale() const { 
    return _sync->Execute([&]() { return _model->GetScale(); });
}

void TransformEntryView::SetOrientation(vsg::dquat value) {
    _sync->Execute([&]() { return _model->SetOrientation(value); });
}

vsg::dquat TransformEntryView::GetOrientation() const { 
    return _sync->Execute([&]() { return _model->GetOrientation(); });
}

void TransformEntryView::Serialize(EntryProperties& properties) const {
    throw std::runtime_error("TransformEntryView is not serializable.");
}

void TransformEntryView::DeserializeInternal(EntryPath path, const EntryProperties& properties) {
    throw std::runtime_error("TransformEntryView is not deserializable.");
}

bool TransformEntryView::IsMutable() const { 
    return _sync->Execute([&]() { return _model->IsMutable(); });
}

void TransformEntryView::CloneFrom(std::shared_ptr<Entry> entry) {
    TransformEntry::CloneFrom(entry);
    assert(std::dynamic_pointer_cast<TransformEntryView>(entry));

    auto e = std::static_pointer_cast<TransformEntryView>(entry);
    this->_model = e->_model;
    this->_sync = e->_sync;
}

std::shared_ptr<Entry> TransformEntryView::CreateCopy() const {
    return std::make_shared<TransformEntryView>();
}
