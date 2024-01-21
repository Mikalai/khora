#pragma once

#include <Fundamental/Interface/IReferenced.h>
#include <string>

namespace Vandrouka::Catalog {

class EntryPath {
public:
  std::string Path;

  EntryPath GetNext() const;
  std::string GetName() const;
  std::string GetLeafName() const;
  EntryPath Append(const std::string name) const;
  bool IsValid() const;
  EntryPath GetParent() const;
};

} // namespace Vandrouka::Catalog::Catalog
