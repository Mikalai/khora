#pragma once

#include <vsg/all.h>

#include <semaphore>

#include "IReferenced.h"

namespace Vandrouka {

class IConfigEntry : public IReferenced {
public:
  virtual bool GetShowTransform() const = 0;
  virtual void SetShowTransform(bool value) = 0;
  virtual bool AddLanguage(const std::string &value) = 0;
  virtual bool RemoveLanguage(const std::string &value) = 0;
  virtual std::vector<std::string> GetLanguages() const = 0;
  virtual std::string GetActiveLanguage() const = 0;
  virtual bool SetActiveLanguage(const std::string &value) = 0;
};

template <> struct GetIID<IConfigEntry> {
  static constexpr InterfaceId Id = {{0x1b, 0xed, 0xbb, 0x53, 0x5d, 0x27, 0x43,
                                      0xc7, 0xa8, 0xb4, 0xc5, 0xe3, 0x9f, 0x3b,
                                      0x21, 0x85}};
};

class ConfigEntry;
template <> struct GetCID<ConfigEntry> {
  static constexpr InterfaceId Id = {{0xf8, 0xee, 0x4a, 0x7b, 0x2, 0x53, 0x48,
                                      0x5d, 0xa8, 0xb8, 0x1, 0xfc, 0x90, 0xc1,
                                      0x2, 0x36}};
};

} // namespace Vandrouka
