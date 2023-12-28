#pragma once

/**
@file
Subclass of TextPanelBase, which is generated by wxFormBuilder.
*/

#include <memory>

#include "../IEntryObserver.h"
#include "../SystemFonts.h"
#include "vsgEditor.h"

//// end generated include
class Entry;
class TextEntry;

/** Implementing TextPanelBase */
class TextPanel : public TextPanelBase,
                  public IEntryObserver,
                  public std::enable_shared_from_this<TextPanel> {
   protected:
    // Handlers for TextPanelBase events.
    void fontCmbOnCombobox(wxCommandEvent& event) override;
    void valueTxtOnText(wxCommandEvent& event) override;

   public:
    /** Constructor */
    TextPanel(wxWindow* parent);
    //// end generated class members

    void SetDataModel(std::shared_ptr<Entry> entry);
    std::shared_ptr<TextEntry> GetDataModel() { return _dataModel; }
    void SetFonts(std::vector<FontInfo> fonts);

    // Inherited via IEntryObserver
    void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) override;
    void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) override;
    void OnPropertyChanged(std::shared_ptr<Entry> sender,
                           std::string_view name) override;
    void OnError(const LogNotification&) const override {}

    void fontColorPickerOnColourChanged(wxColourPickerEvent& event) override;
    void offsetXEditOnText(wxCommandEvent& event) override;
    void offsetYEditOnText(wxCommandEvent& event) override;
    void offsetZEditOnText(wxCommandEvent& event) override;
    void horAxisXEditOnText(wxCommandEvent& event) override;
    void horAxisYEditOnText(wxCommandEvent& event) override;
    void horAxisZEditOnText(wxCommandEvent& event) override;
    void vertAxisXEditOnText(wxCommandEvent& event) override;
    void vertAxisYEditOnText(wxCommandEvent& event) override;
    void vertAxisZEditOnText(wxCommandEvent& event) override;
    void horAlignmentOnCombobox(wxCommandEvent& event) override;
    void vertAlignmentOnCombobox(wxCommandEvent& event) override;
    void lineSpacingEditOnText(wxCommandEvent& event) override;

   private:
    void UpdateControls();

   private:
    std::shared_ptr<TextEntry> _dataModel;
};