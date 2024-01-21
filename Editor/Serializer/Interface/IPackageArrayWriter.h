#pragma once

#include <cstdint>
#include <filesystem>
#include <span>
#include <string_view>

#include <Fundamental/Interface/IReferenced.h>
#include <Fundamental/Interface/Result.h>

namespace Vandrouka::Serializer {

class IPackage;
class IPackageArrayWriter;
class IPackageWriter;
class IPackageArrayReader;
class IPackageReader;

class IPackageArrayWriter : public Fundamental::IReferenced {
public:
  virtual Result<Ref<IPackageArrayWriter>> Add(std::int8_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::uint8_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::int16_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::uint16_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::int32_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::uint32_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::int64_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(std::uint64_t value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(float value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(double value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(const std::string &value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(const std::u8string &value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(const std::wstring &value) = 0;
  virtual Result<Ref<IPackageArrayWriter>> Add(Ref<IPackage> value) = 0;

  virtual Result<Ref<IPackageWriter>> BeginPackage() = 0;
  virtual Result<void> EndPackage() = 0;
};

} // namespace Vandrouka::Serializer

DECLARE_IID(Vandrouka::Serializer::IPackageArrayWriter, 0x7, 0x93, 0x76, 0x5f,
            0xdc, 0x7d, 0x43, 0xfd, 0x87, 0xd9, 0xba, 0xcd, 0x47, 0xf, 0x3b,
            0x60);
