#pragma once

#include "GeometryEntry.h"
#include "Clone.h"

EntryType GeometryEntry::GetType() const {
    return EntryType::Geometry;
}

std::shared_ptr<Entry> GeometryEntry::Clone() {
    return std::make_shared<GeometryEntry>(_geometry);
}

vsg::ref_ptr<vsg::VertexIndexDraw> GeometryEntry::GetGeometry() {
    return ::Clone(_geometry);
}