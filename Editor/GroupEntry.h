#pragma once

#include <vsg/all.h>
#include "DirectoryEntry.h"

class GroupEntry final : public DirectoryEntry {

public:

    GroupEntry()
        : _group{vsg::Group::create()}
    {
    }

    vsg::ref_ptr<vsg::Group> GetGroup();

private:
    vsg::ref_ptr<vsg::Group> _group;

    // Inherited via DirectoryEntry
    EntryType GetType() const override;
    std::shared_ptr<Entry> Clone() override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;

    // Inherited via DirectoryEntry
    std::shared_ptr<Entry> CreateProxy(std::shared_ptr<Entry> root, EntryPath path) override;
};
