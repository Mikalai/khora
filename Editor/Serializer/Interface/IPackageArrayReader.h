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

class IPackageArrayReader : public Fundamental::IReferenced {
public:
  virtual std::int32_t GetSize() const = 0;

  virtual Result<std::int8_t> Int8At(std::int32_t index) const = 0;
  virtual Result<std::uint8_t> UIntAt(std::int32_t index) const = 0;

  virtual Result<std::int16_t> Int16At(std::int32_t index) const = 0;
  virtual Result<std::uint16_t> UInt16At(std::int32_t index) const = 0;

  virtual Result<std::int32_t> Int32At(std::int32_t index) const = 0;
  virtual Result<std::uint32_t> UInt32At(std::int32_t index) const = 0;

  virtual Result<std::int64_t> Int64At(std::int32_t index) const = 0;
  virtual Result<std::uint64_t> UInt64At(std::int32_t index) const = 0;

  virtual Result<float> FloatAt(std::int32_t index) = 0;
  virtual Result<double> DoubleAt(std::int32_t index) = 0;

  virtual Result<std::string> StringAt(std::int32_t index) = 0;

  virtual Result<std::u8string> Utf8StringAt(std::int32_t index) = 0;

  virtual Result<std::wstring> WideString(std::int32_t index) = 0;

  virtual Result<Ref<IPackageReader>> PackageAt(std::int32_t index) = 0;
};

} // namespace Vandrouka::Serializer

DECLARE_IID(Vandrouka::Serializer::IPackageArrayReader, 0xbb, 0x2, 0x3f, 0x9b,
            0xd0, 0xb6, 0x46, 0x7d, 0x8d, 0x64, 0xdd, 0xc2, 0x64, 0xa8, 0x46,
            0x4b);
