#include "LocalizedEntry.h"

void LocalizedEntry::CloneFrom(std::shared_ptr<Entry> entry) {
    GroupEntry::CloneFrom(entry);
}

std::shared_ptr<Entry> LocalizedEntry::CreateCopy() const {
    return std::make_shared<LocalizedEntry>();
}
