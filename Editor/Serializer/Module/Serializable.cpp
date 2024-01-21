#include <Fundamental/Module/Referenced.h>
#include <Serializer/Interface/ISerializable.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Serializer.h"

namespace Vandrouka::Serializer::Private {

class IJsonPackage : public Fundamental::IReferenced {
public:
  virtual nlohmann::json &GetJson() = 0;
};

class JsonPackage final
    : public Fundamental::Private::ReferenceCountedBase<
          JsonPackage, IJsonPackage, IPackage, IPackageWriter, IPackageReader,
          IPackageArrayWriter, IPackageArrayReader> {
  nlohmann::json _o;

  std::string _currentName;
  Ref<IPackageArrayWriter> _currentArrayWriter;
  Ref<IPackageWriter> _currentWriter;

public:
  using Interfaces = Fundamental::Private::QueryInterfaces<
      JsonPackage, IJsonPackage, IPackage, IPackageWriter, IPackageReader,
      IPackageArrayWriter, IPackageArrayReader, IReferenced>;

  JsonPackage() {}
  explicit JsonPackage(nlohmann::json o) : _o(o) {}

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::int8_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  virtual Result<Ref<IPackageWriter>>
  WriteVector3D(std::string_view name, double x, double y, double z) override {
    auto o = _o[name];
    o["x"] = x;
    o["y"] = y;
    o["z"] = z;
    return {Ref<IPackageWriter>{this}};
  }

  virtual Result<Ref<IPackageWriter>> WriteVector4D(std::string_view name,
                                                    double x, double y,
                                                    double z,
                                                    double w) override {
    auto o = _o[name];
    o["x"] = x;
    o["y"] = y;
    o["z"] = z;
    o["w"] = w;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> WriteVector2D(std::string_view name, double x,
                                            double y) override {
    auto o = _o[name];
    o["x"] = x;
    o["y"] = y;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> WriteVector2D(std::string_view name,
                                            std::span<double, 2> p) override {
    auto o = _o[name];
    o["x"] = p[0];
    o["y"] = p[1];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> WriteVector3D(std::string_view name,
                                            std::span<double, 3> p) override {
    auto o = _o[name];
    o["x"] = p[0];
    o["y"] = p[1];
    o["z"] = p[2];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> WriteVector4D(std::string_view name,
                                            std::span<double, 4> p) override {
    auto o = _o[name];
    o["x"] = p[0];
    o["y"] = p[1];
    o["z"] = p[2];
    o["w"] = p[3];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>>
  WriteVector2D(std::string_view name,
                const std::array<double, 2> &p) override {
    auto o = _o[name];
    o["x"] = p[0];
    o["y"] = p[1];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>>
  WriteVector3D(std::string_view name,
                const std::array<double, 3> &p) override {
    auto o = _o[name];
    o["x"] = p[0];
    o["y"] = p[1];
    o["z"] = p[2];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>>
  WriteVector4D(std::string_view name,
                const std::array<double, 4> &p) override {
    auto o = _o[name];
    o["x"] = p[0];
    o["y"] = p[1];
    o["z"] = p[2];
    o["w"] = p[3];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>>
  WriteColor(std::string_view name, const std::array<double, 4> &p) override {
    auto o = _o[name];
    o["r"] = p[0];
    o["g"] = p[1];
    o["b"] = p[2];
    o["a"] = p[3];
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    bool value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::uint8_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::int16_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::uint16_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::int32_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::uint32_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::int64_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    std::uint64_t value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    float value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    double value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    const std::string &value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    const std::u8string &value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    const std::wstring &value) override {
    _o[name] = value;
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> Write(std::string_view name,
                                    Ref<IPackage> value) override {
    if (auto j = value.Cast<IJsonPackage>(); j) {
      _o[name] = j->GetJson();
      return {Ref<IPackageWriter>{this}};
    } else {
      return CreateError(LOG_NOT_IMPLEMENTED, std::string("IPackage"));
    }
  }

  Result<Ref<IPackage>> CreatePackage() override {
    return {Ref<IPackage>{new JsonPackage()}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::int8_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::uint8_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::int16_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::uint16_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::int32_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::uint32_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::int64_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(std::uint64_t value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(float value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(double value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(const std::string &value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(const std::u8string &value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(const std::wstring &value) override {
    _o.push_back(value);
    return {Ref<IPackageArrayWriter>{this}};
  }

  Result<Ref<IPackageArrayWriter>> Add(Ref<IPackage> value) override {
    if (auto j = value.Cast<IJsonPackage>(); j) {
      _o.push_back(j->GetJson());
      return {Ref<IPackageArrayWriter>{this}};
    }
    return CreateError(LOG_NOT_IMPLEMENTED, std::string("IJsonPackage"));
  }

  nlohmann::json &GetJson() override { return this->_o; }

  Result<void> ReadFromFile(std::filesystem::path path) override {

    std::ifstream stream(path, std::ios::binary);

    if (!stream.is_open()) {
      return CreateError(EDITOR_ERROR_FILE_NOT_FOUND, path.string());
    }

    std::string text((std::istreambuf_iterator<char>(stream)),
                     std::istreambuf_iterator<char>());

    try {
      _o = nlohmann::json::parse(text);
    } catch (const std::exception &e) {
      return CreateError(EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID,
                         e.what() + text);
    }

    return {};
  }

  // Inherited via ReferenceCountedBase
  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::int8_t &value) override {
    value = ::Deserialize(this->_o, name, std::int8_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::uint8_t &value) override {
    value = ::Deserialize(this->_o, name, std::uint8_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::int16_t &value) override {
    value = ::Deserialize(this->_o, name, std::int16_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::uint16_t &value) override {
    value = ::Deserialize(this->_o, name, std::uint16_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::int32_t &value) override {
    value = ::Deserialize(this->_o, name, std::int32_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::uint32_t &value) override {
    value = ::Deserialize(this->_o, name, std::uint32_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::int64_t &value) override {
    value = ::Deserialize(this->_o, name, std::int64_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::uint64_t &value) override {
    value = ::Deserialize(this->_o, name, std::uint64_t{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   float &value) override {
    value = ::Deserialize(this->_o, name, float{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   double &value) override {
    value = ::Deserialize(this->_o, name, double{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::string &value) override {
    value = ::Deserialize(this->_o, name, std::string{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::u8string &value) override {
    value = ::Deserialize(this->_o, name, std::u8string{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   std::wstring &value) override {
    value = ::Deserialize(this->_o, name, std::wstring{});
    return {Ref<IPackageReader>{this}};
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   Ref<IPackage> &value) override {
    if (auto it = this->_o.find(name); it != this->_o.end()) {
      auto key = it.key();
      auto v = it.value();
      value = {new JsonPackage{v}};
      return {Ref<IPackageReader>{this}};
    } else {
      return CreateError(LOG_ENTRY_NOT_FOUND, std::string(name));
    }
  }

  Result<Ref<IPackageArrayReader>> ReadArray(std::string_view name) override {
    Ref<IPackage> r;
    Read(name, r);
    return r.Cast<IPackageArrayReader>();
  }

  Result<Ref<IPackageReader>> ReadPackage(std::string_view name) override {
    Ref<IPackage> r;
    Read(name, r);
    return r.Cast<IPackageReader>();
  }

  Result<Ref<IPackageWriter>> GetWriter() override {
    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageReader>> GetReader() override {
    return {Ref<IPackageReader>{this}};
  }

  // Inherited via ReferenceCountedBase
  Result<std::string> ReadString(std::string_view name) override {
    std::string r;
    return Read(name, r) _next_ { return Result<std::string>{r}; };
  }

  Result<std::u8string> ReadUtf8String(std::string_view name) override {
    std::u8string r;
    if (auto result = Read(name, r); result) {
      return r;
    } else {
      return result.Error();
    }
  }

  Result<std::array<double, 3>> ReadVector3D(std::string_view name) override {
    auto o = _o[name];
    std::array<double, 3> result;
    result[0] = o["x"].get<double>();
    result[1] = o["y"].get<double>();
    result[2] = o["z"].get<double>();
    return result;
  }

  Result<std::array<double, 4>> ReadVector4D(std::string_view name) override {
    auto o = _o[name];
    std::array<double, 4> result;
    result[0] = o["x"].get<double>();
    result[1] = o["y"].get<double>();
    result[2] = o["z"].get<double>();
    result[3] = o["w"].get<double>();
    return result;
  }

  Result<double> ReadDouble(std::string_view name) override {
    double r;
    if (auto result = Read(name, r); result) {
      return r;
    } else {
      return result.Error();
    }
  }

  Result<bool> ReadBool(std::string_view name) override {
    bool r;
    if (auto result = Read(name, r); result) {
      return r;
    } else {
      return result.Error();
    }
  }

  Result<Ref<IPackageReader>> Read(std::string_view name,
                                   bool &value) override {
    value = ::Deserialize(this->_o, name, bool{});
    return {Ref<IPackageReader>{this}};
  }

  Result<std::array<double, 4>> ReadColor(std::string_view name) override {
    auto o = _o[name];
    std::array<double, 4> result;
    result[0] = o["r"].get<double>();
    result[1] = o["g"].get<double>();
    result[2] = o["b"].get<double>();
    result[3] = o["a"].get<double>();
    return result;
  }

  std::int32_t GetSize() const override {
    if (this->_o.is_array()) {
      auto size = this->_o.size();
      return static_cast<std::int32_t>(size);
    } else {
      return 0;
    }
  }

  Result<std::int8_t> Int8At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::int8_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::uint8_t> UIntAt(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::uint8_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::int16_t> Int16At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::int16_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::uint16_t> UInt16At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::uint16_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::int32_t> Int32At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::int32_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::uint32_t> UInt32At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::uint32_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::int64_t> Int64At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::int64_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::uint64_t> UInt64At(std::int32_t index) const override {
    if (index < GetSize()) {
      return {this->_o[index].get<std::uint64_t>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<float> FloatAt(std::int32_t index) override {
    if (index < GetSize()) {
      return {this->_o[index].get<float>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<double> DoubleAt(std::int32_t index) override {
    if (index < GetSize()) {
      return {this->_o[index].get<double>()};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::string> StringAt(std::int32_t index) override {
    if (index < GetSize()) {
      try {
        assert(this->_o.is_array());
        auto value = this->_o.at((size_t)index);
        return {value.get<std::string>()};
      } catch (const std::exception &e) {
        return CreateError(LOG_FILE_LOAD_FAILED, std::string{e.what()});
      }
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<std::u8string> Utf8StringAt(std::int32_t index) override {
    if (index < GetSize()) {
      assert(this->_o.is_array());
      return {
          std::u8string((char8_t *)this->_o[index].get<std::string>().c_str())};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }
  Result<std::wstring> WideString(std::int32_t index) override {
    if (index < GetSize()) {
      return {
          std::filesystem::path(this->_o[index].get<std::string>()).wstring(),
      };
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<Ref<IPackageReader>> PackageAt(std::int32_t index) override {
    if (index < GetSize()) {
      auto o = this->_o[index];
      return {Ref<IPackageReader>(new JsonPackage{std::move(o)})};
    } else {
      return CreateError(LOG_INDEX_OUT_OF_RANGE, std::string{"Index"});
    }
  }

  Result<void> WriteToFile(std::filesystem::path path) override {
    try {

      auto str = this->_o.dump(4);

      if (std::filesystem::exists(path)) {
        std::filesystem::copy_file(
            path, path.string() + ".old",
            std::filesystem::copy_options::overwrite_existing);
      }

      std::ofstream stream(path, std::ios::binary);
      if (stream.is_open()) {
        stream.write(str.data(), str.size());
      }
    } catch (const std::exception &e) {
      return CreateError(EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID,
                         e.what() + std::string(". ") + path.string());
    }
    return {};
  }

  // Inherited via ReferenceCountedBase
  Result<Ref<IPackageWriter>> BeginPackage(std::string_view name) override {
    assert(!_currentWriter);
    assert(!_currentArrayWriter);
    if (_currentWriter || _currentArrayWriter) {
      return CreateError(LOG_OPERATION_NOT_SUPPORTED,
                         std::string{"BeginPackage"});
    }
    _currentName = name;
    _currentWriter = new JsonPackage{};
    return {_currentWriter};
  }

  Result<void> EndPackage() override {
    assert(_currentWriter);
    if (!_currentWriter) {
      return CreateError(LOG_OPERATION_NOT_SUPPORTED,
                         std::string{"EndPackage"});
    }

    if (auto json = _currentWriter.Cast<IJsonPackage>(); json) {
      if (_currentName.empty()) {
        this->_o.push_back(json->GetJson());
      } else {
        this->_o[_currentName] = json->GetJson();
      }
      _currentWriter.Reset();
    } else {
      return CreateError(LOG_NOT_IMPLEMENTED, std::string{"EndPackage"});
    }
    return {};
  }

  Result<Ref<IPackageArrayWriter>> BeginArray(std::string_view name) override {
    assert(!_currentWriter);
    assert(!_currentArrayWriter);
    if (_currentWriter || _currentArrayWriter) {
      return CreateError(LOG_OPERATION_NOT_SUPPORTED,
                         std::string{"BeginArray"});
    }
    _currentName = name;
    _currentArrayWriter = new JsonPackage{};
    return {_currentArrayWriter};
  }

  Result<Ref<IPackageWriter>> EndArray() override {
    assert(_currentArrayWriter);
    if (!_currentArrayWriter) {
      return CreateError(LOG_OPERATION_NOT_SUPPORTED, std::string{"EndArray"});
    }

    if (auto json = _currentArrayWriter.Cast<IJsonPackage>(); json) {
      this->_o[_currentName] = json->GetJson();
      _currentArrayWriter.Reset();
    } else {
      return CreateError(LOG_NOT_IMPLEMENTED, std::string{"EndPackage"});
    }

    return {Ref<IPackageWriter>{this}};
  }

  Result<Ref<IPackageWriter>> BeginPackage() override {
    assert(!_currentWriter);
    assert(!_currentArrayWriter);
    if (_currentWriter || _currentArrayWriter) {
      return CreateError(LOG_OPERATION_NOT_SUPPORTED,
                         std::string{"BeginPackage"});
    }
    _currentName.clear();
    _currentWriter = new JsonPackage{};
    return {_currentWriter};
  }
};

} // namespace Vandrouka::Serializer::Private

DECLARE_IID(Vandrouka::Serializer::Private::IJsonPackage, 0x7d, 0x8b, 0xec, 0x2,
            0x38, 0x75, 0x4d, 0xe9, 0x85, 0xa9, 0x7e, 0xf6, 0xcc, 0x3a, 0x6f,
            0xe0);

namespace Vandrouka::Factory {

IReferenced *CreateJsonPackage() {
  // static_assert(std::derived_from<::Vandrouka::AsyncQueue, IReferenced>,
  // "AsyncQueue is not IReferenced");
  return (Serializer::Private::IJsonPackage
              *)new Serializer::Private::JsonPackage();
}

} // namespace Vandrouka::Factory