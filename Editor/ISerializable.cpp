#include "ISerializable.h"
#include <nlohmann/json.hpp>

namespace Vandrouka {

class IJsonPackage : public IReferenced {
public:
  virtual nlohmann::json &GetJson() = 0;
};

template <> struct GetIID<IAsyncTask> {
  static constexpr InterfaceId Id = {{0x7d, 0x8b, 0xec, 0x2, 0x38, 0x75, 0x4d,
                                      0xe9, 0x85, 0xa9, 0x7e, 0xf6, 0xcc, 0x3a,
                                      0x6f, 0xe0}};
};

class JsonPackage final
    : public ReferenceCountedBase<JsonPackage, IJsonPackage, IPackage,
                                  IPackageWriter, IPackageArrayWriter> {
  nlohmann::json _o;

public:
  bool Write(std::string_view name, std::int8_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::uint8_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::int16_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::uint16_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::int32_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::uint32_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::int64_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, std::uint64_t value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, float value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, double value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, const std::string &value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, const std::u8string &value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, const std::wstring &value) override {
    _o[name] = value;
    return true;
  }

  bool Write(std::string_view name, Ref<IPackage> value) override {
    if (auto j = value.Cast<IJsonPackage>(); j) {
      _o[name] = j->GetJson();
      return true;
    }
    return false;
  }

  Ref<IPackageArray> CreatePackage() override { return new JsonPackage(); }

  bool Add(std::int8_t value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(std::uint8_t value) override {
    _o.push_back(value);
    return true;
  }

  bool Add(std::int16_t value) override {
    _o.push_back(value);
    return true;
  }

  bool Add(std::uint16_t value) override {
    _o.push_back(value);
    return true;
  }

  bool Add(std::int32_t value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(std::uint32_t value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(std::int64_t value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(std::uint64_t value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(float value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(double value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(const std::string &value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(const std::u8string &value) override {
    _o.push_back(value);
    return true;
  }
  bool Add(const std::wstring &value) override {
    _o.push_back(value);
    return true;
  }

  bool Add(Ref<IPackage> value) override {
    if (auto j = value.Cast<IJsonPackage>(); j) {
      _o.push_back(j->GetJson());
      return true;
    }
    return false;
  }
};
} // namespace Vandrouka
