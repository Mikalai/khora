#pragma once

#include <cstdint>
#include <filesystem>
#include <span>
#include <string_view>

#include "Errors.h"
#include "IReferenced.h"

namespace Vandrouka {

class IPackage;
class IPackageArrayWriter;
class IPackageWriter;
class IPackageArrayReader;
class IPackageReader;

class IPackage : public IReferenced {
public:
  virtual Result<Ref<IPackage>> CreatePackage() = 0;
  virtual Result<Ref<IPackageWriter>> GetWriter() = 0;
  virtual Result<Ref<IPackageReader>> GetReader() = 0;
  virtual Result<void> ReadFromFile(std::filesystem::path path) = 0;
  virtual Result<void> WriteToFile(std::filesystem::path path) = 0;
};

template <> struct GetIID<IPackage> {
  static constexpr InterfaceId Id = {{0xc4, 0x38, 0x8c, 0xc2, 0x17, 0x68, 0x4e,
                                      0x8b, 0x94, 0x9e, 0xdd, 0xb9, 0x8d, 0xa7,
                                      0x30, 0xae}};
};

class IPackageWriter : public IReferenced {
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

template <> struct GetIID<IPackageWriter> {
  static constexpr InterfaceId Id = {{0x30, 0xe5, 0x51, 0x6a, 0x3, 0xca, 0x45,
                                      0x99, 0xb5, 0x8b, 0x61, 0x19, 0xdc, 0x91,
                                      0xad, 0x80}};
};

class IPackageReader : public IReferenced {
public:
  virtual Result<Ref<IPackageReader>> Read(std::string_view name,
                                           bool& value) = 0;
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

template <> struct GetIID<IPackageReader> {
  static constexpr InterfaceId Id = {{0x13, 0xe1, 0x1c, 0x17, 0x9c, 0x84, 0x4b,
                                      0x50, 0x83, 0xee, 0x43, 0xcd, 0x3d, 0xc2,
                                      0x21, 0x2c}};
};

class IPackageArrayWriter : public IReferenced {
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

template <> struct GetIID<IPackageArrayWriter> {
  static constexpr InterfaceId Id = {{0x7, 0x93, 0x76, 0x5f, 0xdc, 0x7d, 0x43,
                                      0xfd, 0x87, 0xd9, 0xba, 0xcd, 0x47, 0xf,
                                      0x3b, 0x60}};
};

class IPackageArrayReader : public IReferenced {
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

template <> struct GetIID<IPackageArrayReader> {
  static constexpr InterfaceId Id = {{0xbb, 0x2, 0x3f, 0x9b, 0xd0, 0xb6, 0x46,
                                      0x7d, 0x8d, 0x64, 0xdd, 0xc2, 0x64, 0xa8,
                                      0x46, 0x4b}};
};

class ISerializable : public IReferenced {
public:
  virtual Result<Ref<IPackageWriter>>
  Serialize(Ref<IPackageWriter> package, Ref<IReferenced> state) const = 0;
  virtual Result<Ref<IPackageReader>> Deserialize(Ref<IPackageReader> package,
                                                  Ref<IReferenced> state) = 0;
};

template <> struct GetIID<ISerializable> {
  static constexpr InterfaceId Id = {{0x2e, 0xc6, 0xc0, 0x30, 0xbd, 0xf8, 0x47,
                                      0xf2, 0xb2, 0x7e, 0x16, 0x4e, 0xf9, 0x60,
                                      0x2d, 0xdf}};
};

class JsonPackage;

template <> struct GetCID<JsonPackage> {
  static constexpr InterfaceId Id = {{0x8d, 0xed, 0x42, 0xd, 0x21, 0xf0, 0x4b,
                                      0x83, 0xbd, 0x16, 0xad, 0x1b, 0x91, 0x70,
                                      0x7c, 0xfe}};
};

} // namespace Vandrouka