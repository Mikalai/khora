#include "LocalizedEntry.h"
#include "DirectoryEntry.h"

namespace Vandrouka::Catalog::Private {

class LocalizedEntry final
    : public DirectoryEntryBase<LocalizedEntry, ILocalizedEntry, IGroupEntry> {
public:
  EntryType GetType() const override { return EntryType::Localized; }
  vsg::ref_ptr<vsg::Group> GetGroup() override { return vsg::Group::create(); }
};

} // namespace Vandrouka::Catalog::Private

namespace Vandrouka::Factory {

IReferenced *CreateLocalizedEntry() {
  static_assert(
      std::is_base_of_v<IReferenced, Catalog::Private::LocalizedEntry>);
  return static_cast<Catalog::ILocalizedEntry *>(
      new Catalog::Private::LocalizedEntry());
}

} // namespace Vandrouka::Factory
