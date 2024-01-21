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

class IPackageWriter : public Fundamental::IReferenced {
public:
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            bool value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::int8_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::uint8_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::int16_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::uint16_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::int32_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::uint32_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::int64_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            std::uint64_t value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            float value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            double value) = 0;
  virtual Result<Ref<IPackageWriter>> WriteVector2D(std::string_view name,
                                                    double x, double y) = 0;
  virtual Result<Ref<IPackageWriter>>
  WriteVector3D(std::string_view name, double x, double y, double z) = 0;
  virtual Result<Ref<IPackageWriter>> WriteVector4D(std::string_view name,
                                                    double x, double y,
                                                    double z, double w) = 0;
  virtual Result<Ref<IPackageWriter>> WriteVector2D(std::string_view name,
                                                    std::span<double, 2> p) = 0;
  virtual Result<Ref<IPackageWriter>> WriteVector3D(std::string_view name,
                                                    std::span<double, 3> p) = 0;
  virtual Result<Ref<IPackageWriter>> WriteVector4D(std::string_view name,
                                                    std::span<double, 4> p) = 0;
  virtual Result<Ref<IPackageWriter>>
  WriteVector2D(std::string_view name, const std::array<double, 2> &p) = 0;
  virtual Result<Ref<IPackageWriter>>
  WriteVector3D(std::string_view name, const std::array<double, 3> &p) = 0;
  virtual Result<Ref<IPackageWriter>>
  WriteVector4D(std::string_view name, const std::array<double, 4> &p) = 0;
  virtual Result<Ref<IPackageWriter>>
  WriteColor(std::string_view name, const std::array<double, 4> &p) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            const std::string &value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            const std::u8string &value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            const std::wstring &value) = 0;
  virtual Result<Ref<IPackageWriter>> Write(std::string_view name,
                                            Ref<IPackage> value) = 0;

  virtual Result<Ref<IPackageWriter>> BeginPackage(std::string_view name) = 0;

  virtual Result<void> EndPackage() = 0;

  virtual Result<Ref<IPackageArrayWriter>>
  BeginArray(std::string_view name) = 0;
  virtual Result<Ref<IPackageWriter>> EndArray() = 0;
};

} // namespace Vandrouka::Serializer

DECLARE_IID(Vandrouka::Serializer::IPackageWriter, 0x30, 0xe5, 0x51, 0x6a, 0x3,
            0xca, 0x45, 0x99, 0xb5, 0x8b, 0x61, 0x19, 0xdc, 0x91, 0xad, 0x80);
