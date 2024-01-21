#pragma once

#include <Fundamental/Interface/Result.h>

namespace Vandrouka::Catalog {

class IConfigEntry : public Fundamental::IReferenced {
public:
  virtual bool GetShowTransform() const = 0;
  virtual Result<bool> SetShowTransform(bool value) = 0;
  virtual Result<bool> AddLanguage(const std::string &value) = 0;
  virtual Result<bool> RemoveLanguage(const std::string &value) = 0;
  virtual std::vector<std::string> GetLanguages() const = 0;
  virtual std::string GetActiveLanguage() const = 0;
  virtual Result<bool> SetActiveLanguage(const std::string &value) = 0;
};

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::IConfigEntry, 0x1b, 0xed, 0xbb, 0x53, 0x5d,
            0x27, 0x43, 0xc7, 0xa8, 0xb4, 0xc5, 0xe3, 0x9f, 0x3b, 0x21, 0x85);

DECLARE_CID(Catalog, ConfigEntry, 0xf8, 0xee, 0x4a, 0x7b, 0x2, 0x53, 0x48, 0x5d,
            0xa8, 0xb8, 0x1, 0xfc, 0x90, 0xc1, 0x2, 0x36);
