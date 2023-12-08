#pragma once

#include <vsg/all.h>
#include "Entry.h"

class GeometryEntry final : public Entry {
public:
    GeometryEntry(vsg::ref_ptr<vsg::VertexIndexDraw> indexedGeometry)
        : _geometry{ indexedGeometry } {
    }

    EntryType GetType() const override;
    std::shared_ptr<Entry> Clone() override;

    vsg::ref_ptr<vsg::VertexIndexDraw> GetGeometry();

private:
    vsg::ref_ptr<vsg::VertexIndexDraw> _geometry;
};

