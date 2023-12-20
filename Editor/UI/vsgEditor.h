///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.0.0-0-g0efcecf)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/combobox.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class EditorMainWindowBase
///////////////////////////////////////////////////////////////////////////////
class EditorMainWindowBase : public wxFrame
{
	private:

	protected:
		wxSplitterWindow* m_splitter2;
		wxPanel* explorerPanel;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel8;
		wxNotebook* dataPanels;
		wxPanel* assetsPage;
		wxTreeCtrl* assetsTree;
		wxPanel* localizationPage;
		wxButton* langAdd;
		wxButton* langRemove;
		wxListBox* languageListBox;
		wxPanel* m_panel9;
		wxComboBox* addToScene;
		wxButton* deleteFromScene;
		wxTreeCtrl* finalScene;
		wxPanel* rightPane;
		wxSplitterWindow* m_splitter31;
		wxPanel* propertiesPanel;
		wxBoxSizer* propertiesSizer;
		wxPanel* renderView;
		wxGridSizer* renderViewSizer;
		wxStatusBar* statusBar;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		wxMenuItem* showTransformMenu;
		wxToolBar* mainToolbar;
		wxToolBarToolBase* navigate;

		// Virtual event handlers, override them in your derived class
		virtual void assetsTreeOnTreeBeginDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void assetsTreeOnTreeEndDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void assetsTreeOnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void langAddOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void langRemoveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void languageListBoxOnListBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void languageListBoxOnListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void addToSceneOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void deleteFromSceneOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void finalSceneOnKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeBeginDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeBeginLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeEndDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeEndLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void loadProjectMenuItemOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveProjectMenuItemOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void resetMenuItemOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnImport( wxCommandEvent& event ) { event.Skip(); }
		virtual void exportMenuOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void showTransformMenuOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void navigateOnToolClicked( wxCommandEvent& event ) { event.Skip(); }


	public:

		EditorMainWindowBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 872,836 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~EditorMainWindowBase();

		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 300 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::m_splitter2OnIdle ), NULL, this );
		}

		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 0 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::m_splitter3OnIdle ), NULL, this );
		}

		void m_splitter31OnIdle( wxIdleEvent& )
		{
			m_splitter31->SetSashPosition( 320 );
			m_splitter31->Disconnect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::m_splitter31OnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class TransformPanelBase
///////////////////////////////////////////////////////////////////////////////
class TransformPanelBase : public wxPanel
{
	private:

	protected:
		wxTextCtrl* txt00;
		wxTextCtrl* txt01;
		wxTextCtrl* txt02;
		wxTextCtrl* txt03;
		wxTextCtrl* txt10;
		wxTextCtrl* txt11;
		wxTextCtrl* txt12;
		wxTextCtrl* txt13;
		wxTextCtrl* txt20;
		wxTextCtrl* txt21;
		wxTextCtrl* txt22;
		wxTextCtrl* txt23;
		wxTextCtrl* txt30;
		wxTextCtrl* txt31;
		wxTextCtrl* txt32;
		wxTextCtrl* txt33;
		wxCheckBox* overrideCheckBox;
		wxStaticText* m_staticText1;
		wxTextCtrl* posTxt0;
		wxTextCtrl* posTxt1;
		wxTextCtrl* posTxt2;
		wxStaticText* m_staticText3;
		wxTextCtrl* scaleTxt0;
		wxTextCtrl* scaleTxt1;
		wxTextCtrl* scaleTxt2;
		wxStaticText* orientLbl;
		wxTextCtrl* orient0;
		wxTextCtrl* orient1;
		wxTextCtrl* orient2;
		wxTextCtrl* orient3;

		// Virtual event handlers, override them in your derived class
		virtual void matrixValueChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void overrideChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void positionChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void scaleChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void orientationChanged( wxCommandEvent& event ) { event.Skip(); }


	public:

		TransformPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 304,263 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~TransformPanelBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TextEnter
///////////////////////////////////////////////////////////////////////////////
class TextEnter : public wxDialog
{
	private:

	protected:
		wxTextCtrl* textEdit;
		wxButton* btnOk;
		wxButton* btnCancel;

		// Virtual event handlers, override them in your derived class
		virtual void textEditOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void btnOkOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btnCancelOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		TextEnter( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~TextEnter();

};

