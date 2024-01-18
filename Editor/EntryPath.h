#pragma once

#include <string>
#include "IReferenced.h"

namespace Vandrouka {

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

} // namespace Vandrouka

struct EntryPath {
  std::string Path;

  EntryPath GetNext() const;
  std::string GetName() const;
  std::string GetLeafName() const;
  EntryPath Append(const std::string name) const;
  bool IsValid() const;
  EntryPath GetParent() const;
};
