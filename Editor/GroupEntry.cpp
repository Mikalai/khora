
#include "GroupEntry.h"

GroupEntry::GroupEntry()
{
}

vsg::ref_ptr<vsg::Group> GroupEntry::GetGroup() {
    return vsg::Group::create();
}

EntryType GroupEntry::GetType() const
{
    return EntryType::Group;
}

bool GroupEntry::CanAdd(std::shared_ptr<Entry> entry)
{
    return true;
}

std::shared_ptr<Entry> GroupEntry::CreateProxy(EntryPath path)
{
    throw std::runtime_error("Group entry is not supposed to have proxies. At least for now.");
}

void GroupEntry::CloneFrom(std::shared_ptr<Entry> entry) {
    DirectoryEntry::CloneFrom(entry);

}

std::shared_ptr<Entry> GroupEntry::CreateCopy() const {
    return std::make_shared<GroupEntry>();
}
