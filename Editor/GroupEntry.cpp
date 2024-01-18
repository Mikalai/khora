#include "GroupEntry.h"
#include "IGroupEntry.h"
#include "IObserver.h"
#include "DirectoryEntry.h"

namespace Vandrouka {

class GroupEntry : public DirectoryEntryBase<GroupEntry, IGroupEntry> {
  using Base = DirectoryEntryBase<GroupEntry, IGroupEntry>;

public:

  EntryType GetType() const override { return EntryType::Group; }

  vsg::ref_ptr<vsg::Group> GetGroup() override { return vsg::Group::create(); }
  
};

IReferenced *CreateGroupEntry() {
  static_assert(std::is_base_of_v<IReferenced, GroupEntry>);
  return static_cast<IGroupEntry *>(new GroupEntry());
}

} // namespace Vandrouka

//GroupEntry::GroupEntry() {}
//
//vsg::ref_ptr<vsg::Group> GroupEntry::GetGroup() { return vsg::Group::create(); }
//
//EntryType GroupEntry::GetType() const { return EntryType::Group; }
//
//bool GroupEntry::CanAdd(std::shared_ptr<Entry>) { return true; }
//
//std::shared_ptr<Entry> GroupEntry::CreateProxy(EntryPath) {
//  throw std::runtime_error(
//      "Group entry is not supposed to have proxies. At least for now.");
//}
//
//void GroupEntry::CloneFrom(std::shared_ptr<Entry> entry) {
//  DirectoryEntry::CloneFrom(entry);
//}
//
//std::shared_ptr<Entry> GroupEntry::CreateCopy() const {
//  return std::make_shared<GroupEntry>();
//}
