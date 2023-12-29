#include "TextPanel.h"

#include <magic_enum.hpp>

#include "../TextEntry.h"
#include "UICommon.h"

TextPanel::TextPanel(wxWindow *parent) : TextPanelBase(parent) {}

void TextPanel::fontCmbOnCombobox(wxCommandEvent &) {
  if (!_dataModel)
    return;
  _dataModel->SetFont(fontCmb->GetValue().ToStdString());
}

void TextPanel::valueTxtOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  auto value = valueTxt->GetValue();
  auto buffer = value.ToUTF8();
  std::u8string ustr{(char8_t *)buffer.data(), buffer.length()};
  _dataModel->SetValue(ustr);
}

void TextPanel::fontColorPickerOnColourChanged(wxColourPickerEvent &event) {
  if (!_dataModel)
    return;
  auto value = event.GetColour();
  auto r = value.Red() / 255.0;
  auto g = value.Green() / 255.0;
  auto b = value.Blue() / 255.0;
  auto a = value.Alpha() / 255.0;
  _dataModel->SetColor(r, g, b, a);
}

void TextPanel::offsetXEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (offsetXEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetOffsetX(value);
  }
}

void TextPanel::offsetYEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (offsetYEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetOffsetY(value);
  }
}

void TextPanel::offsetZEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (offsetZEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetOffsetZ(value);
  }
}

void TextPanel::horAxisXEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (horAxisXEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetHorizontalAxisX(value);
  }
}

void TextPanel::horAxisYEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (horAxisYEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetHorizontalAxisY(value);
  }
}

void TextPanel::horAxisZEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (horAxisZEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetHorizontalAxisZ(value);
  }
}

void TextPanel::vertAxisXEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (vertAxisXEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetVerticalAxisX(value);
  }
}

void TextPanel::vertAxisYEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (vertAxisYEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetVerticalAxisY(value);
  }
}

void TextPanel::vertAxisZEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (vertAxisZEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetVerticalAxisZ(value);
  }
}

void TextPanel::horAlignmentOnCombobox(wxCommandEvent &) {
  if (!_dataModel)
    return;
  auto value = magic_enum::enum_cast<TextHorizontalAlignment>(
                   horAlignment->GetValue().ToStdString())
                   .value_or(TextHorizontalAlignment::Center);
  _dataModel->SetHorizontalAlignment(value);
}

void TextPanel::vertAlignmentOnCombobox(wxCommandEvent &) {
  if (!_dataModel)
    return;
  auto value = magic_enum::enum_cast<TextVerticalAlignment>(
                   vertAlignment->GetValue().ToStdString())
                   .value_or(TextVerticalAlignment::Center);
  _dataModel->SetVerticalAlignment(value);
}

void TextPanel::lineSpacingEditOnText(wxCommandEvent &) {
  if (!_dataModel)
    return;
  double value;
  if (lineSpacingEdit->GetValue().ToCDouble(&value)) {
    _dataModel->SetLineSpacing(value);
  }
}

void TextPanel::SetDataModel(std::shared_ptr<Entry> entry) {
  if (_dataModel) {
    _dataModel->RemoveObserver(shared_from_this());
  }

  _dataModel = std::dynamic_pointer_cast<TextEntry>(entry);

  if (_dataModel) {
    _dataModel->AddObserver(shared_from_this());
    UpdateControls();
    this->Show(true);
  } else {
    this->Show(false);
  }
}

void TextPanel::UpdateControls() {
  if (!_dataModel)
    return;

  fontCmb->SetValue(_dataModel->GetFont());
  auto value = _dataModel->GetValue();
  auto str = wxString::FromUTF8((char *)value.c_str());
  valueTxt->SetValue(str);

  offsetXEdit->SetValue(wxString::FromCDouble(_dataModel->GetOffsetX()));
  offsetYEdit->SetValue(wxString::FromCDouble(_dataModel->GetOffsetY()));
  offsetZEdit->SetValue(wxString::FromCDouble(_dataModel->GetOffsetZ()));

  horAxisXEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetHorizontalAxisX()));
  horAxisYEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetHorizontalAxisY()));
  horAxisZEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetHorizontalAxisZ()));

  vertAxisXEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetVerticalAxisX()));
  vertAxisYEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetVerticalAxisY()));
  vertAxisZEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetVerticalAxisZ()));

  auto r = (std::uint8_t)(_dataModel->GetColorR() * 255.0);
  auto g = (std::uint8_t)(_dataModel->GetColorG() * 255.0);
  auto b = (std::uint8_t)(_dataModel->GetColorB() * 255.0);
  auto a = (std::uint8_t)(_dataModel->GetColorA() * 255.0);
  fontColorPicker->SetColour(wxColour(r, g, b, a));

  horAlignment->SetValue(
      std::string(magic_enum::enum_name(_dataModel->GetHorizontalAlignment())));
  vertAlignment->SetValue(
      std::string(magic_enum::enum_name(_dataModel->GetVerticalAlignment())));

  lineSpacingEdit->SetValue(
      wxString::FromCDouble(_dataModel->GetLineSpacing()));
}

void TextPanel::OnEntryAdded(EntryPath, std::shared_ptr<Entry> entry) {
  if (_dataModel != entry)
    return;
}

void TextPanel::OnEntryRemoved(EntryPath, std::shared_ptr<Entry> entry) {
  if (_dataModel != entry)
    return;
}

void TextPanel::OnPropertyChanged(std::shared_ptr<Entry> sender,
                                  std::string_view) {
  if (_dataModel != sender)
    return;
}

void TextPanel::SetFonts(std::vector<FontInfo> fonts) {
  fontCmb->Clear();
  for (auto &fnt : fonts) {
    fontCmb->Append(fnt.GetDisplayName());
  }
  if (_dataModel) {
    fontCmb->SetValue(_dataModel->GetFont());
  }
}