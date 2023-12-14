///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.0.0-0-g0efcecf)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "vsgEditor.h"

///////////////////////////////////////////////////////////////////////////

EditorMainWindowBase::EditorMainWindowBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	m_splitter2 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->SetSashGravity( 0 );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::m_splitter2OnIdle ), NULL, this );
	m_splitter2->SetMinimumPaneSize( 100 );

	explorerPanel = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_splitter3 = new wxSplitterWindow( explorerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::m_splitter3OnIdle ), NULL, this );

	m_panel8 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	assetsTree = new wxTreeCtrl( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
	bSizer9->Add( assetsTree, 1, wxEXPAND, 0 );


	m_panel8->SetSizer( bSizer9 );
	m_panel8->Layout();
	bSizer9->Fit( m_panel8 );
	m_panel9 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	finalScene = new wxTreeCtrl( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
	bSizer10->Add( finalScene, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	deleteFromScene = new wxButton( m_panel9, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( deleteFromScene, 0, wxALL, 5 );


	bSizer10->Add( bSizer51, 0, wxEXPAND, 5 );


	m_panel9->SetSizer( bSizer10 );
	m_panel9->Layout();
	bSizer10->Fit( m_panel9 );
	m_splitter3->SplitHorizontally( m_panel8, m_panel9, 0 );
	bSizer5->Add( m_splitter3, 1, wxEXPAND, 5 );


	explorerPanel->SetSizer( bSizer5 );
	explorerPanel->Layout();
	bSizer5->Fit( explorerPanel );
	renderView = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	renderView->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	renderViewSizer = new wxGridSizer( 1, 1, 0, 0 );


	renderView->SetSizer( renderViewSizer );
	renderView->Layout();
	renderViewSizer->Fit( renderView );
	m_splitter2->SplitVertically( explorerPanel, renderView, 300 );
	bSizer1->Add( m_splitter2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* loadProjectMenuItem;
	loadProjectMenuItem = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Load Project") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( loadProjectMenuItem );

	wxMenuItem* saveProjectMenuItem;
	saveProjectMenuItem = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Save Project") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	saveProjectMenuItem->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	saveProjectMenuItem->SetBitmap( wxNullBitmap );
	#endif
	m_menu1->Append( saveProjectMenuItem );

	wxMenuItem* resetMenuItem;
	resetMenuItem = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Reset Project") ) + wxT('\t') + wxT("Ctrl+R"), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( resetMenuItem );

	m_menu1->AppendSeparator();

	wxMenuItem* importMenuItem;
	importMenuItem = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Import") ) + wxT('\t') + wxT("Ctrl+I"), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( importMenuItem );

	m_menubar1->Append( m_menu1, wxT("File") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	assetsTree->Connect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeBeginDrag ), NULL, this );
	assetsTree->Connect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeEndDrag ), NULL, this );
	assetsTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeSelChanged ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeBeginDrag ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeEndDrag ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeSelChanged ), NULL, this );
	deleteFromScene->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::deleteFromSceneOnButtonClick ), NULL, this );
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::loadProjectMenuItemOnMenuSelection ), this, loadProjectMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::saveProjectMenuItemOnMenuSelection ), this, saveProjectMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::resetMenuItemOnMenuSelection ), this, resetMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::OnImport ), this, importMenuItem->GetId());
}

EditorMainWindowBase::~EditorMainWindowBase()
{
	// Disconnect Events
	assetsTree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeBeginDrag ), NULL, this );
	assetsTree->Disconnect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeEndDrag ), NULL, this );
	assetsTree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeSelChanged ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeBeginDrag ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeEndDrag ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeSelChanged ), NULL, this );
	deleteFromScene->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::deleteFromSceneOnButtonClick ), NULL, this );

}
