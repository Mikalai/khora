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

class IPackage : public Fundamental::IReferenced {
public:
  virtual Result<Ref<IPackage>> CreatePackage() = 0;
  virtual Result<Ref<IPackageWriter>> GetWriter() = 0;
  virtual Result<Ref<IPackageReader>> GetReader() = 0;
  virtual Result<void> ReadFromFile(std::filesystem::path path) = 0;
  virtual Result<void> WriteToFile(std::filesystem::path path) = 0;
};

} // namespace Vandrouka::Serializer

DECLARE_IID(Vandrouka::Serializer::IPackage, 0xc4, 0x38, 0x8c, 0xc2, 0x17, 0x68,
            0x4e, 0x8b, 0x94, 0x9e, 0xdd, 0xb9, 0x8d, 0xa7, 0x30, 0xae);
