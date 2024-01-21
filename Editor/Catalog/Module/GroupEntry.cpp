#include "GroupEntry.h"
#include "DirectoryEntry.h"
#include <Catalog/Interface/IGroupEntry.h>
#include <Fundamental/Interface/IObserver.h>

namespace Vandrouka::Catalog::Private {

class GroupEntry : public DirectoryEntryBase<GroupEntry, IGroupEntry> {
  using Base = DirectoryEntryBase<GroupEntry, IGroupEntry>;

public:
  EntryType GetType() const override { return EntryType::Group; }

  vsg::ref_ptr<vsg::Group> GetGroup() override { return vsg::Group::create(); }
};

} // namespace Vandrouka::Catalog::Private

namespace Vandrouka::Factory {

IReferenced *CreateGroupEntry() {
  static_assert(std::is_base_of_v<IReferenced, Catalog::Private::GroupEntry>);
  return static_cast<Catalog::IGroupEntry *>(
      new Catalog::Private::GroupEntry());
}

} // namespace Vandrouka::Factory
