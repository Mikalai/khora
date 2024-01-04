#pragma once

#include "GroupEntry.h"
#include "ILocalizedEntry.h"

class LocalizedEntry : public GroupEntry {
public:
  EntryType GetType() const override { return EntryType::Localized; }

protected:
  void CloneFrom(std::shared_ptr<Entry> entry) override;
  std::shared_ptr<Entry> CreateCopy() const override;
};
