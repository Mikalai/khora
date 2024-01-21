#pragma once

#include <cstdint>
#include <filesystem>
#include <span>
#include <string_view>

#include <Fundamental/Interface/Result.h>
#include <Fundamental/Interface/IReferenced.h>
#include <Serializer/Interface/IPackage.h>
#include <Serializer/Interface/IPackageArrayReader.h>
#include <Serializer/Interface/IPackageArrayWriter.h>
#include <Serializer/Interface/IPackageReader.h>
#include <Serializer/Interface/IPackageWriter.h>

namespace Vandrouka::Serializer {

class ISerializable : public Fundamental::IReferenced {
public:
  virtual Result<Ref<IPackageWriter>>
  Serialize(Ref<IPackageWriter> package, Ref<IReferenced> state) const = 0;
  virtual Result<Ref<IPackageReader>> Deserialize(Ref<IPackageReader> package,
                                                  Ref<IReferenced> state) = 0;
};

} // namespace Vandrouka

DECLARE_IID(Vandrouka::Serializer::ISerializable, 0x2e, 0xc6, 0xc0, 0x30, 0xbd,
            0xf8, 0x47, 0xf2, 0xb2,
            0x7e, 0x16, 0x4e, 0xf9, 0x60, 0x2d, 0xdf);

DECLARE_CID(Serializer, JsonPackage, 0x8d, 0xed, 0x42, 0xd, 0x21, 0xf0, 0x4b,
            0x83, 0xbd, 0x16, 0xad, 0x1b, 0x91, 0x70, 0x7c, 0xfe);
