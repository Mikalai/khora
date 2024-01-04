#include "TextEntry.h"

#include <magic_enum.hpp>

#include "AsyncQueue.h"
#include "Clone.h"
#include "Errors.h"
#include "Serializer.h"

namespace Vandrouka {

class TextEntry : public EntryBase<TextEntry, IEntry, ITextEntry, IObservable> {
public:
  bool QueryInterface(const InterfaceId &id, void **o) override {

    if (id == GetIID<IEntry>::Id) {
      *o = static_cast<IEntry *>(this);
    } else if (id == GetIID<ITextEntry>::Id) {
      *o = static_cast<ITextEntry *>(this);
    } else if (id == GetIID<IObservable>::Id) {
      *o = static_cast<IObservable *>(this);
    } else if (id == GetIID<IReferenced>::Id) {
      *o = static_cast<IReferenced *>(static_cast<IEntry *>(this));
    } else {
      *o = nullptr;
    }

    if (*o) {
      this->AddRef();
    }

    return *o != nullptr;
  }

  EntryType GetType() const override { return EntryType::Text; }

  void SetFont(const std::string &fontName) override {
    if (_fontName == fontName)
      return;

    _fontName = fontName;
    OnPropertyChanged("Font");
  }

  std::string GetFont() const override { return _fontName; }

  void SetValue(const std::u8string &value) override {
    if (_value == value)
      return;

    _value = value;
    OnPropertyChanged("Value");
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

  void SetOffsetX(double value) override {
    if (_offset[0] == value)
      return;

    _offset[0] = value;
    OnPropertyChanged("Offset.X");
  }

  void SetOffsetY(double value) override {
    if (_offset[1] == value)
      return;

    _offset[1] = value;
    OnPropertyChanged("Offset.Y");
  }

  void SetOffsetZ(double value) {
    if (_offset[2] == value)
      return;

    _offset[2] = value;
    OnPropertyChanged("Offset.Z");
  }

  void SetHorizontalAxisX(double value) override {
    if (_horAxis[0] == value)
      return;

    _horAxis[0] = value;
    OnPropertyChanged("HorizontalAxis.X");
  }

  void SetHorizontalAxisY(double value) override {
    if (_horAxis[1] == value)
      return;

    _horAxis[1] = value;
    OnPropertyChanged("HorizontalAxis.Y");
  }

  void SetHorizontalAxisZ(double value) override {
    if (_horAxis[2] == value)
      return;

    _horAxis[2] = value;
    OnPropertyChanged("HorizontalAxis.Z");
  }

  void SetVerticalAxisX(double value) override {
    if (_vertAxis[0] == value)
      return;

    _vertAxis[0] = value;
    OnPropertyChanged("VerticalAxis.X");
  }

  void SetVerticalAxisY(double value) override {
    if (_vertAxis[1] == value)
      return;

    _vertAxis[1] = value;
    OnPropertyChanged("VerticalAxis.Y");
  }

  void SetVerticalAxisZ(double value) override {
    if (_vertAxis[2] == value)
      return;

    _vertAxis[2] = value;
    OnPropertyChanged("VerticalAxis.Z");
  }

  void SetColor(double r, double g, double b, double a) {
    if (r == _color[0] && g == _color[1] && b == _color[2] && a == _color[3])
      return;

    _color[0] = r;
    _color[1] = g;
    _color[2] = b;
    _color[3] = a;

    OnPropertyChanged("Color");
  }

  void SetColorR(double value) override {
    if (_color[0] == value)
      return;

    _color[0] = value;
    OnPropertyChanged("Color.R");
  }

  void SetColorG(double value) override {
    if (_color[1] == value)
      return;

    _color[1] = value;
    OnPropertyChanged("Color.G");
  }

  void SetColorB(double value) override {
    if (_color[2] == value)
      return;

    _color[2] = value;
    OnPropertyChanged("Color.B");
  }

  void SetColorA(double value) override {
    if (_color[3] == value)
      return;

    _color[3] = value;
    OnPropertyChanged("Color.A");
  }

  void SetHorizontalAlignment(TextHorizontalAlignment value) override {
    if (_horAlignment == value)
      return;

    _horAlignment = value;
    OnPropertyChanged("HorizontalAlignment");
  }

  void SetVerticalAlignment(TextVerticalAlignment value) override {
    if (_vertAlignment == value)
      return;

    _vertAlignment = value;
    OnPropertyChanged("VerticalAlignment");
  }

  void SetLineSpacing(double value) {
    if (_lineSpacing == value)
      return;

    _lineSpacing = value;
    OnPropertyChanged("LineSpacing");
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

IReferenced *CreateTextEntry() { return (IEntry *)(new TextEntry()); }
} // namespace Vandrouka

TextEntry::TextEntry() {}

TextEntry::TextEntry(const TextEntry &entry) : Entry{entry} {}

EntryType TextEntry::GetType() const { return EntryType::Text; }

std::shared_ptr<Entry> TextEntry::CreateView(std::shared_ptr<AsyncQueue> sync) {
  assert(std::dynamic_pointer_cast<TextEntry>(shared_from_this()));
  return std::make_shared<TextEntryView>(
      std::static_pointer_cast<TextEntry>(shared_from_this()), sync);
}

std::shared_ptr<Entry> TextEntry::CreateProxy(EntryPath) {
  OnError(LogError(LOG_OPERATION_NOT_SUPPORTED, "TextEntry::CreateProxy"));
  return {};
}

std::shared_ptr<Entry> TextEntry::CreateCopy() const {
  return std::make_shared<TextEntry>();
}

void TextEntry::CloneFrom(std::shared_ptr<Entry> entry) {
  Entry::CloneFrom(entry);

  assert(std::dynamic_pointer_cast<TextEntry>(entry));
  auto e = std::static_pointer_cast<TextEntry>(entry);

  this->_fontName = e->_fontName;
  this->_value = e->_value;

  this->_offset = e->_offset;
  this->_horAxis = e->_horAxis;
  this->_vertAxis = e->_vertAxis;
  this->_color = e->_color;
  this->_horAlignment = e->_horAlignment;
  this->_vertAlignment = e->_vertAlignment;
  this->_lineSpacing = e->_lineSpacing;
}

void TextEntry::SetOffsetX(double value) {
  if (_offset[0] == value)
    return;

  _offset[0] = value;
  OnPropertyChanged(shared_from_this(), "Offset.X");
}

void TextEntry::SetOffsetY(double value) {
  if (_offset[1] == value)
    return;

  _offset[1] = value;
  OnPropertyChanged(shared_from_this(), "Offset.Y");
}

void TextEntry::SetOffsetZ(double value) {
  if (_offset[2] == value)
    return;

  _offset[2] = value;
  OnPropertyChanged(shared_from_this(), "Offset.Z");
}

void TextEntry::SetHorizontalAxisX(double value) {
  if (_horAxis[0] == value)
    return;

  _horAxis[0] = value;
  OnPropertyChanged(shared_from_this(), "HorizontalAxis.X");
}

void TextEntry::SetHorizontalAxisY(double value) {
  if (_horAxis[1] == value)
    return;

  _horAxis[1] = value;
  OnPropertyChanged(shared_from_this(), "HorizontalAxis.Y");
}

void TextEntry::SetHorizontalAxisZ(double value) {
  if (_horAxis[2] == value)
    return;

  _horAxis[2] = value;
  OnPropertyChanged(shared_from_this(), "HorizontalAxis.Z");
}

void TextEntry::SetVerticalAxisX(double value) {
  if (_vertAxis[0] == value)
    return;

  _vertAxis[0] = value;
  OnPropertyChanged(shared_from_this(), "VerticalAxis.X");
}

void TextEntry::SetVerticalAxisY(double value) {
  if (_vertAxis[1] == value)
    return;

  _vertAxis[1] = value;
  OnPropertyChanged(shared_from_this(), "VerticalAxis.Y");
}

void TextEntry::SetVerticalAxisZ(double value) {
  if (_vertAxis[2] == value)
    return;

  _vertAxis[2] = value;
  OnPropertyChanged(shared_from_this(), "VerticalAxis.Z");
}

void TextEntry::SetColor(double r, double g, double b, double a) {
  if (r == _color[0] && g == _color[1] && b == _color[2] && a == _color[3])
    return;

  _color[0] = r;
  _color[1] = g;
  _color[2] = b;
  _color[3] = a;

  OnPropertyChanged(shared_from_this(), "Color");
}

void TextEntry::SetColorR(double value) {
  if (_color[0] == value)
    return;

  _color[0] = value;
  OnPropertyChanged(shared_from_this(), "Color.R");
}

void TextEntry::SetColorG(double value) {
  if (_color[1] == value)
    return;

  _color[1] = value;
  OnPropertyChanged(shared_from_this(), "Color.G");
}

void TextEntry::SetColorB(double value) {
  if (_color[2] == value)
    return;

  _color[2] = value;
  OnPropertyChanged(shared_from_this(), "Color.B");
}

void TextEntry::SetColorA(double value) {
  if (_color[3] == value)
    return;

  _color[3] = value;
  OnPropertyChanged(shared_from_this(), "Color.A");
}

void TextEntry::SetHorizontalAlignment(TextHorizontalAlignment value) {
  if (_horAlignment == value)
    return;

  _horAlignment = value;
  OnPropertyChanged(shared_from_this(), "HorizontalAlignment");
}

void TextEntry::SetVerticalAlignment(TextVerticalAlignment value) {
  if (_vertAlignment == value)
    return;

  _vertAlignment = value;
  OnPropertyChanged(shared_from_this(), "VerticalAlignment");
}

void TextEntry::SetLineSpacing(double value) {
  if (_lineSpacing == value)
    return;

  _lineSpacing = value;
  OnPropertyChanged(shared_from_this(), "LineSpacing");
}

void TextEntry::SetFont(const std::string &fontName) {
  if (_fontName == fontName)
    return;

  _fontName = fontName;
  OnPropertyChanged(shared_from_this(), "Font");
}

void TextEntry::SetValue(const std::u8string &value) {
  if (_value == value)
    return;

  _value = value;
  OnPropertyChanged(shared_from_this(), "Value");
}

void TextEntry::Serialize(EntryProperties &properties) const {
  Entry::Serialize(properties);

  properties["Font"] = _fontName;
  ::Serialize(properties["Value"], _value);

  ::SerializeVector(properties["Offset"], _offset);
  ::SerializeVector(properties["HorizontalAxis"], _horAxis);
  ::SerializeVector(properties["VerticalAxis"], _vertAxis);
  ::SerializeColor(properties["Color"], _color);

  properties["HorizontalAlignment"] = magic_enum::enum_name(_horAlignment);
  properties["VerticalAlignment"] = magic_enum::enum_name(_vertAlignment);

  properties["LineSpacing"] = _lineSpacing;
}

void TextEntry::DeserializeInternal(EntryPath path,
                                    const EntryProperties &properties) {
  Entry::DeserializeInternal(path, properties);

  _fontName = ::Deserialize(properties, "Font", std::string{});
  _value = ::Deserialize(properties, "Value", std::u8string{});

  _offset = ::DeserializeVector(properties, "Offset", {{0, 0, 0}});
  _horAxis = ::DeserializeVector(properties, "HorizontalAxis", {{1, 0, 0}});
  _vertAxis = ::DeserializeVector(properties, "VerticalAxis", {{0, 0, 1}});
  _color = ::DeserializeColor(properties, "Color", {{0, 0, 0, 1}});

  _horAlignment =
      magic_enum::enum_cast<TextHorizontalAlignment>(
          ::Deserialize(properties, "HorizontalAlignment", std::string{}))
          .value_or(TextHorizontalAlignment::Center);
  _vertAlignment =
      magic_enum::enum_cast<TextVerticalAlignment>(
          ::Deserialize(properties, "VerticalAlignment", std::string{}))
          .value_or(TextVerticalAlignment::Center);

  _lineSpacing = ::Deserialize(properties, "LineSpacing", 1.0);
}

std::shared_ptr<Entry> TextEntryView::CreateProxy(EntryPath path) {
  return _sync->Execute([&]() { return _model->CreateProxy(path); });
}

void TextEntryView::SetFont(const std::string &font) {
  _sync->Execute([&]() { return _model->SetFont(font); });
}

std::string TextEntryView::GetFont() const {
  return _sync->Execute([&]() { return _model->GetFont(); });
}

void TextEntryView::SetValue(const std::u8string &value) {
  _sync->Execute([&]() { return _model->SetValue(value); });
}

std::u8string TextEntryView::GetValue() const {
  return _sync->Execute([&]() { return _model->GetValue(); });
}

double TextEntryView::GetOffsetX() const {
  return _sync->Execute([&]() { return _model->GetOffsetX(); });
}

double TextEntryView::GetOffsetY() const {
  return _sync->Execute([&]() { return _model->GetOffsetY(); });
}

double TextEntryView::GetOffsetZ() const {
  return _sync->Execute([&]() { return _model->GetOffsetZ(); });
}

double TextEntryView::GetHorizontalAxisX() const {
  return _sync->Execute([&]() { return _model->GetHorizontalAxisX(); });
}

double TextEntryView::GetHorizontalAxisY() const {
  return _sync->Execute([&]() { return _model->GetHorizontalAxisY(); });
}

double TextEntryView::GetHorizontalAxisZ() const {
  return _sync->Execute([&]() { return _model->GetHorizontalAxisZ(); });
}

double TextEntryView::GetVerticalAxisX() const {
  return _sync->Execute([&]() { return _model->GetVerticalAxisX(); });
}

double TextEntryView::GetVerticalAxisY() const {
  return _sync->Execute([&]() { return _model->GetVerticalAxisY(); });
}

double TextEntryView::GetVerticalAxisZ() const {
  return _sync->Execute([&]() { return _model->GetVerticalAxisZ(); });
}

void TextEntryView::SetColor(double r, double g, double b, double a) {
  _sync->Execute([&]() { return _model->SetColor(r, g, b, a); });
}

double TextEntryView::GetColorR() const {
  return _sync->Execute([&]() { return _model->GetColorR(); });
}

double TextEntryView::GetColorG() const {
  return _sync->Execute([&]() { return _model->GetColorG(); });
}

double TextEntryView::GetColorB() const {
  return _sync->Execute([&]() { return _model->GetColorB(); });
}

double TextEntryView::GetColorA() const {
  return _sync->Execute([&]() { return _model->GetColorA(); });
}

TextHorizontalAlignment TextEntryView::GetHorizontalAlignment() const {
  return _sync->Execute([&]() { return _model->GetHorizontalAlignment(); });
}

TextVerticalAlignment TextEntryView::GetVerticalAlignment() const {
  return _sync->Execute([&]() { return _model->GetVerticalAlignment(); });
}

double TextEntryView::GetLineSpacing() const {
  return _sync->Execute([&]() { return _model->GetLineSpacing(); });
}

void TextEntryView::SetOffsetX(double value) {
  _sync->Execute([&]() { return _model->SetOffsetX(value); });
}

void TextEntryView::SetOffsetY(double value) {
  _sync->Execute([&]() { return _model->SetOffsetY(value); });
}

void TextEntryView::SetOffsetZ(double value) {
  _sync->Execute([&]() { return _model->SetOffsetZ(value); });
}

void TextEntryView::SetHorizontalAxisX(double value) {
  _sync->Execute([&]() { return _model->SetHorizontalAxisX(value); });
}

void TextEntryView::SetHorizontalAxisY(double value) {
  _sync->Execute([&]() { return _model->SetHorizontalAxisY(value); });
}

void TextEntryView::SetHorizontalAxisZ(double value) {
  _sync->Execute([&]() { return _model->SetHorizontalAxisZ(value); });
}

void TextEntryView::SetVerticalAxisX(double value) {
  _sync->Execute([&]() { return _model->SetVerticalAxisX(value); });
}

void TextEntryView::SetVerticalAxisY(double value) {
  _sync->Execute([&]() { return _model->SetVerticalAxisY(value); });
}

void TextEntryView::SetVerticalAxisZ(double value) {
  _sync->Execute([&]() { return _model->SetVerticalAxisZ(value); });
}

void TextEntryView::SetColorR(double value) {
  _sync->Execute([&]() { return _model->SetColorR(value); });
}

void TextEntryView::SetColorG(double value) {
  _sync->Execute([&]() { return _model->SetColorG(value); });
}

void TextEntryView::SetColorB(double value) {
  _sync->Execute([&]() { return _model->SetColorB(value); });
}

void TextEntryView::SetColorA(double value) {
  _sync->Execute([&]() { return _model->SetColorA(value); });
}

void TextEntryView::SetHorizontalAlignment(TextHorizontalAlignment value) {
  _sync->Execute([&]() { return _model->SetHorizontalAlignment(value); });
}

void TextEntryView::SetVerticalAlignment(TextVerticalAlignment value) {
  _sync->Execute([&]() { return _model->SetVerticalAlignment(value); });
}

void TextEntryView::SetLineSpacing(double value) {
  _sync->Execute([&]() { return _model->SetLineSpacing(value); });
}

void TextEntryView::Serialize(EntryProperties &) const {
  OnError(LogError(LOG_OPERATION_NOT_SUPPORTED, "TextEntryView::Serialize"));
}

void TextEntryView::DeserializeInternal(EntryPath, const EntryProperties &) {
  OnError(LogError(LOG_OPERATION_NOT_SUPPORTED,
                   "TextEntryView::DeserializeInternal"));
}

void TextEntryView::CloneFrom(std::shared_ptr<Entry> entry) {
  TextEntry::CloneFrom(entry);
  assert(std::dynamic_pointer_cast<TextEntryView>(entry));

  auto e = std::static_pointer_cast<TextEntryView>(entry);
  this->_model = e->_model;
  this->_sync = e->_sync;
}

std::shared_ptr<Entry> TextEntryView::CreateCopy() const {
  return std::make_shared<TextEntryView>();
}
