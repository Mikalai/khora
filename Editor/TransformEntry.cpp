#pragma once

#include "TransformEntry.h"
#include "Clone.h"

EntryType TransformEntry::GetType() const {
    return EntryType::Transform;
}

vsg::ref_ptr<vsg::MatrixTransform> TransformEntry::GetTransform() const {
    return ::Clone(_transform);
}

std::shared_ptr<Entry> TransformEntry::Clone()
{
    return std::make_shared<TransformEntry>(::Clone(_transform));
}

bool TransformEntry::CanAdd(std::shared_ptr<Entry> entry)
{
    return true;
}