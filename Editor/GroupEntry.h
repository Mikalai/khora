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
    EntryType GetType() const override;
    std::shared_ptr<Entry> Clone() override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

private:
    vsg::ref_ptr<vsg::Group> _group;
};
