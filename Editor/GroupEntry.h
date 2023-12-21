#pragma once

#include <vsg/all.h>
#include "DirectoryEntry.h"

class GroupEntry : public DirectoryEntry {

public:

    GroupEntry();

    vsg::ref_ptr<vsg::Group> GetGroup();
    EntryType GetType() const override;
    bool CanAdd(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

    std::shared_ptr<Entry> CreateView(std::shared_ptr<AsyncQueue> sync) { return {}; }


protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;
};
