#include "LocalizedEntry.h"

namespace Vandrouka {

class LocalizedEntry
    : public DirectoryEntryBase<LocalizedEntry, ILocalizedEntry, IGroupEntry> {
public:
  EntryType GetType() const override { return EntryType::Localized; }
  vsg::ref_ptr<vsg::Group> GetGroup() override { return vsg::Group::create(); }
};

IReferenced *CreateLocalizedEntry() {
  static_assert(std::is_base_of_v<IReferenced, LocalizedEntry>);
  return static_cast<ILocalizedEntry *>(new LocalizedEntry());
}

} // namespace Vandrouka

void LocalizedEntry::CloneFrom(std::shared_ptr<Entry> entry) {
  GroupEntry::CloneFrom(entry);
}

std::shared_ptr<Entry> LocalizedEntry::CreateCopy() const {
  return std::make_shared<LocalizedEntry>();
}
