
#include "GroupEntry.h"

vsg::ref_ptr<vsg::Group> GroupEntry::GetGroup() {
    return vsg::Group::create();
}

EntryType GroupEntry::GetType() const
{
    return EntryType::Group;
}

std::shared_ptr<Entry> GroupEntry::Clone()
{
    return std::make_shared<GroupEntry>();
}

bool GroupEntry::CanAdd(std::shared_ptr<Entry> entry)
{
    return true;
}

std::shared_ptr<Entry> GroupEntry::CreateProxy(std::shared_ptr<Entry> root, EntryPath path)
{
    throw std::runtime_error("Group entry is not supposed to have proxies. At least for now.");
}
