#include "UICommon.h"
#include "TextEnterDialog.h"

TextEnterDialog::TextEnterDialog(const wxString& title, wxWindow* parent)
    : TextEnter(parent)
{
    this->SetTitle(title);
}

wxString TextEnterDialog::GetText() const {
    return textEdit->GetValue();
}

void TextEnterDialog::SetText(const wxString& value) {
    textEdit->SetValue(value);
}

void TextEnterDialog::textEditOnText(wxCommandEvent& event) {
    event.Skip();
}

void TextEnterDialog::btnOkOnButtonClick(wxCommandEvent& event) {
    this->EndModal(wxID_OK);
}

void TextEnterDialog::btnCancelOnButtonClick(wxCommandEvent& event) {
    this->EndModal(wxID_CANCEL);
}
