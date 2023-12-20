#include "UICommon.h"
#include "TextEnterDialog.h"

TextEnterDialog::TextEnterDialog( wxWindow* parent )
:
TextEnter( parent )
{

}

wxString TextEnterDialog::GetText() const {
    return textEdit->GetValue();
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
