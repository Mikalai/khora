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

class IPackageReader : public Fundamental::IReferenced {
public:
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           bool &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::int8_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::uint8_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::int16_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::uint16_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::int32_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::uint32_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::int64_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::uint64_t &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           float &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           double &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::string &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::u8string &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           std::wstring &value) = 0;
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           Ref<IPackage> &value) = 0;

  virtual Result<Ref<IPackageReader>> ReadPackage(std::string_view name) = 0;
  virtual Result<Ref<IPackageArrayReader>> ReadArray(std::string_view name) = 0;
  virtual Result<std::string> ReadString(std::string_view name) = 0;
  virtual Result<std::u8string> ReadUtf8String(std::string_view name) = 0;
  virtual Result<std::array<double, 3>> ReadVector3D(std::string_view name) = 0;
  virtual Result<std::array<double, 4>> ReadVector4D(std::string_view name) = 0;
  virtual Result<std::array<double, 4>> ReadColor(std::string_view name) = 0;
  virtual Result<double> ReadDouble(std::string_view name) = 0;
  virtual Result<bool> ReadBool(std::string_view name) = 0;
};

} // namespace Vandrouka::Serializer

DECLARE_IID(Vandrouka::Serializer::IPackageReader, 0x13, 0xe1, 0x1c, 0x17, 0x9c,
            0x84, 0x4b, 0x50, 0x83, 0xee, 0x43, 0xcd, 0x3d, 0xc2, 0x21, 0x2c);
