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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>

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
		wxTreeCtrl* assetsTree;
		wxPanel* m_panel9;
		wxTreeCtrl* finalScene;
		wxButton* deleteFromScene;
		wxPanel* renderView;
		wxGridSizer* renderViewSizer;
		wxStatusBar* statusBar;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;

		// Virtual event handlers, override them in your derived class
		virtual void assetsTreeOnTreeBeginDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void assetsTreeOnTreeEndDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void assetsTreeOnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeBeginDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeEndDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void finalSceneOnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void deleteFromSceneOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void loadProjectMenuItemOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveProjectMenuItemOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnImport( wxCommandEvent& event ) { event.Skip(); }


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

};

