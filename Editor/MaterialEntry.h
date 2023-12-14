#pragma once

#include <vsg/all.h>
#include "DirectoryEntry.h"

class MaterialEntry final : public DirectoryEntry {
public:

    MaterialEntry(vsg::ref_ptr<vsg::StateGroup> state)
        : _state { state } {
    }

    EntryType GetType() const override;
    std::shared_ptr<Entry> Clone() override;

    vsg::ref_ptr<vsg::StateGroup> GetState() const;

private:
    vsg::ref_ptr<vsg::StateGroup> _state;    

    // Inherited via DirectoryEntry
    bool CanAdd(std::shared_ptr<Entry> entry) override;
};
