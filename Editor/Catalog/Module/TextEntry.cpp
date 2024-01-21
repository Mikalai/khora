#include "TextEntry.h"

#include <magic_enum.hpp>

#include <Catalog/Module/Clone.h>
#include <Catalog/Module/EntryBase.h>
#include <Fundamental/Module/AsyncQueue.h>
#include <Serializer/Interface/ISerializable.h>

namespace Vandrouka::Catalog::Private {

class TextEntry : public EntryBase<TextEntry, ITextEntry, IEntry,
                                   Serializer::ISerializable> {
  using Base =
      EntryBase<TextEntry, ITextEntry, IEntry, Serializer::ISerializable>;

public:
  EntryType GetType() const override { return EntryType::Text; }

  Result<bool> SetFont(const std::string &fontName) override {
    if (_fontName == fontName)
      return false;

    _fontName = fontName;
    return true;
  }

  std::string GetFont() const override { return _fontName; }

  Result<bool> SetValue(const std::u8string &value) override {
    if (_value == value)
      return false;

    _value = value;
    return true;
  }
  std::u8string GetValue() const override { return _value; }

  double GetOffsetX() const override { return _offset[0]; }
  double GetOffsetY() const override { return _offset[1]; }
  double GetOffsetZ() const override { return _offset[2]; }

  double GetHorizontalAxisX() const override { return _horAxis[0]; }
  double GetHorizontalAxisY() const override { return _horAxis[1]; }
  double GetHorizontalAxisZ() const override { return _horAxis[2]; }

  double GetVerticalAxisX() const override { return _vertAxis[0]; }
  double GetVerticalAxisY() const override { return _vertAxis[1]; }
  double GetVerticalAxisZ() const override { return _vertAxis[2]; }

  double GetColorR() const override { return _color[0]; }
  double GetColorG() const override { return _color[1]; }
  double GetColorB() const override { return _color[2]; }
  double GetColorA() const override { return _color[3]; }

  TextHorizontalAlignment GetHorizontalAlignment() const override {
    return _horAlignment;
  }

  TextVerticalAlignment GetVerticalAlignment() const override {
    return _vertAlignment;
  }

  double GetLineSpacing() const override { return _lineSpacing; }

  Result<bool> SetOffsetX(double value) override {
    if (_offset[0] == value)
      return false;

    _offset[0] = value;
    return true;
  }

  Result<bool> SetOffsetY(double value) override {
    if (_offset[1] == value)
      return false;

    _offset[1] = value;
    return true;
  }

  Result<bool> SetOffsetZ(double value) {
    if (_offset[2] == value)
      return false;

    _offset[2] = value;
    return true;
  }

  Result<bool> SetHorizontalAxisX(double value) override {
    if (_horAxis[0] == value)
      return false;

    _horAxis[0] = value;
    return true;
  }

  Result<bool> SetHorizontalAxisY(double value) override {
    if (_horAxis[1] == value)
      return false;

    _horAxis[1] = value;
    return true;
  }

  Result<bool> SetHorizontalAxisZ(double value) override {
    if (_horAxis[2] == value)
      return false;

    _horAxis[2] = value;
    return true;
  }

  Result<bool> SetVerticalAxisX(double value) override {
    if (_vertAxis[0] == value)
      return false;

    _vertAxis[0] = value;
    return true;
  }

  Result<bool> SetVerticalAxisY(double value) override {
    if (_vertAxis[1] == value)
      return false;

    _vertAxis[1] = value;
    return true;
  }

  Result<bool> SetVerticalAxisZ(double value) override {
    if (_vertAxis[2] == value)
      return false;

    _vertAxis[2] = value;
    return true;
  }

  Result<bool> SetColor(double r, double g, double b, double a) {
    if (r == _color[0] && g == _color[1] && b == _color[2] && a == _color[3])
      return false;

    _color[0] = r;
    _color[1] = g;
    _color[2] = b;
    _color[3] = a;

    return true;
  }

  Result<bool> SetColorR(double value) override {
    if (_color[0] == value)
      return false;

    _color[0] = value;
    return true;
  }

  Result<bool> SetColorG(double value) override {
    if (_color[1] == value)
      return false;

    _color[1] = value;
    return true;
  }

  Result<bool> SetColorB(double value) override {
    if (_color[2] == value)
      return false;

    _color[2] = value;
    return true;
  }

  Result<bool> SetColorA(double value) override {
    if (_color[3] == value)
      return false;

    _color[3] = value;
    return true;
  }

  Result<bool> SetHorizontalAlignment(TextHorizontalAlignment value) override {
    if (_horAlignment == value)
      return false;

    _horAlignment = value;
    return true;
  }

  Result<bool> SetVerticalAlignment(TextVerticalAlignment value) override {
    if (_vertAlignment == value)
      return false;

    _vertAlignment = value;
    return true;
  }

  Result<bool> SetLineSpacing(double value) {
    if (_lineSpacing == value)
      return false;

    _lineSpacing = value;
    return true;
  }

  Result<Ref<Serializer::IPackageWriter>>
  SerializeInternal(Ref<Serializer::IPackageWriter> writer) const override {
    Base::SerializeInternal(writer);

    writer->Write("Font", _fontName);
    writer->Write("Value", _value);

    writer->WriteVector3D("Offset", _offset);
    writer->WriteVector3D("HorizontalAxis", _horAxis);
    writer->WriteVector3D("VerticalAxis", _vertAxis);
    writer->WriteColor("Color", _color);

    writer->Write("HorizontalAlignment",
                  std::string(magic_enum::enum_name(_horAlignment)));
    writer->Write("VerticalAlignment",
                  std::string(magic_enum::enum_name(_vertAlignment)));

    writer->Write("LineSpacing", _lineSpacing);

    return writer;
  }

  Result<Ref<Serializer::IPackageReader>>
  DeserializeInternal(Ref<IEntryPathStateWrapper> state,
                      Ref<Serializer::IPackageReader> reader) override {

    Base::DeserializeInternal(state, reader);

    _fontName = reader->ReadString("Font").Value({});
    _value = reader->ReadUtf8String("Value").Value({});

    _offset = reader->ReadVector3D("Offset").Value({0, 0, 0});
    _horAxis = reader->ReadVector3D("HorizontalAxis").Value({1, 0, 0});
    _vertAxis = reader->ReadVector3D("VerticalAxis").Value({0, 0, 1});
    _color = reader->ReadColor("Color").Value({0, 0, 0, 1});

    _horAlignment = magic_enum::enum_cast<TextHorizontalAlignment>(
                        reader->ReadString("HorizontalAlignment").Value({}))
                        .value_or(TextHorizontalAlignment::Center);

    _vertAlignment = magic_enum::enum_cast<TextVerticalAlignment>(
                         reader->ReadString("VerticalAlignment").Value({}))
                         .value_or(TextVerticalAlignment::Center);

    _lineSpacing = reader->ReadDouble("LineSpacing").Value(1.0);

    return reader;
  }

private:
  std::string _fontName;
  std::u8string _value;

  std::array<double, 3> _offset{{0, 0, 0}};
  std::array<double, 3> _horAxis{{1, 0, 0}};
  std::array<double, 3> _vertAxis{{0, 0, 1}};
  std::array<double, 4> _color{{0, 0, 0, 1}};

  TextHorizontalAlignment _horAlignment{TextHorizontalAlignment::Center};
  TextVerticalAlignment _vertAlignment{TextVerticalAlignment::Center};

  double _lineSpacing{1.0};
};

} // namespace Vandrouka::Catalog::Private

namespace Vandrouka::Factory {

IReferenced *CreateTextEntry() {
  return (Catalog::IEntry *)(new Catalog::Private::TextEntry());
}

} // namespace Vandrouka::Factory
