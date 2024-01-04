#pragma once

#include "IReferenced.h"
#include <cstdint>
#include <string_view>

namespace Vandrouka {

class IPackage;

class IPackage : public IReferenced {
public:
  virtual Ref<IPackage> CreatePackage() = 0;
};

class IPackageWriter : public IReferenced {
public:
  virtual bool Write(std::string_view name, std::int8_t value) = 0;
  virtual bool Write(std::string_view name, std::uint8_t value) = 0;
  virtual bool Write(std::string_view name, std::int16_t value) = 0;
  virtual bool Write(std::string_view name, std::uint16_t value) = 0;
  virtual bool Write(std::string_view name, std::int32_t value) = 0;
  virtual bool Write(std::string_view name, std::uint32_t value) = 0;
  virtual bool Write(std::string_view name, std::int64_t value) = 0;
  virtual bool Write(std::string_view name, std::uint64_t value) = 0;
  virtual bool Write(std::string_view name, float value) = 0;
  virtual bool Write(std::string_view name, double value) = 0;
  virtual bool Write(std::string_view name, const std::string &value) = 0;
  virtual bool Write(std::string_view name, const std::u8string &value) = 0;
  virtual bool Write(std::string_view name, const std::wstring &value) = 0;
  virtual bool Write(std::string_view name, Ref<IPackage> value) = 0;
};

class IPackageArrayWriter : public IReferenced {
public:
  virtual bool Add(std::int8_t value) = 0;
  virtual bool Add(std::uint8_t value) = 0;
  virtual bool Add(std::int16_t value) = 0;
  virtual bool Add(std::uint16_t value) = 0;
  virtual bool Add(std::int32_t value) = 0;
  virtual bool Add(std::uint32_t value) = 0;
  virtual bool Add(std::int64_t value) = 0;
  virtual bool Add(std::uint64_t value) = 0;
  virtual bool Add(float value) = 0;
  virtual bool Add(double value) = 0;
  virtual bool Add(const std::string &value) = 0;
  virtual bool Add(const std::u8string &value) = 0;
  virtual bool Add(const std::wstring &value) = 0;
  virtual bool Add(Ref<IPackage> value) = 0;
};

class ISerializable : public IReferenced {
public:
  virtual void Serialize(Ref<IPackage> package) const;
  virtual void Deserialize(Ref<IPackage> package) const;
};

} // namespace Vandrouka