#include "TextEnterDialog.h"

#include "UICommon.h"

TextEnterDialog::TextEnterDialog(const wxString& title, wxWindow* parent)
    : TextEnter(parent) {
    this->SetTitle(title);
}

wxString TextEnterDialog::GetText() const { return textEdit->GetValue(); }

void TextEnterDialog::SetText(const wxString& value) {
    textEdit->SetValue(value);
}

void TextEnterDialog::textEditOnText(wxCommandEvent& event) { event.Skip(); }

void TextEnterDialog::btnOkOnButtonClick(wxCommandEvent&) {
    this->EndModal(wxID_OK);
}

void TextEnterDialog::btnCancelOnButtonClick(wxCommandEvent&) {
    this->EndModal(wxID_CANCEL);
}
