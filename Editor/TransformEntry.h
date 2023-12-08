#pragma once

#include <vsg/all.h>
#include "DirectoryEntry.h"

class TransformEntry final : public DirectoryEntry {
public:

    TransformEntry(vsg::ref_ptr<vsg::MatrixTransform> transform)
        : _transform { transform } {
    }

    EntryType GetType() const override;
    std::shared_ptr<Entry> Clone() override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;

    vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const;

private:
    vsg::ref_ptr<vsg::MatrixTransform> _transform;
};



