///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.0.0-0-g0efcecf)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "UICommon.h"

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
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer6->AddGrowableCol( 0 );
	fgSizer6->AddGrowableCol( 1 );
	fgSizer6->AddGrowableRow( 0 );
	fgSizer6->AddGrowableRow( 1 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	dataPanels = new wxNotebook( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxSize dataPanelsImageSize = wxSize( 16,16 );
	int dataPanelsIndex = 0;
	wxImageList* dataPanelsImages = new wxImageList( dataPanelsImageSize.GetWidth(), dataPanelsImageSize.GetHeight() );
	dataPanels->AssignImageList( dataPanelsImages );
	wxBitmap dataPanelsBitmap;
	wxImage dataPanelsImage;
	assetsPage = new wxPanel( dataPanels, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableCol( 1 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->AddGrowableRow( 1 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	assetsTree = new wxTreeCtrl( assetsPage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
	fgSizer8->Add( assetsTree, 1, wxALL|wxEXPAND, 0 );


	assetsPage->SetSizer( fgSizer8 );
	assetsPage->Layout();
	fgSizer8->Fit( assetsPage );
	dataPanels->AddPage( assetsPage, wxT("Assets"), false );
	dataPanelsBitmap = wxArtProvider::GetBitmap( ArtIconAssets, wxART_FRAME_ICON );
	if ( dataPanelsBitmap.Ok() )
	{
		dataPanelsImage = dataPanelsBitmap.ConvertToImage();
		dataPanelsImages->Add( dataPanelsImage.Scale( dataPanelsImageSize.GetWidth(), dataPanelsImageSize.GetHeight() ) );
		dataPanels->SetPageImage( dataPanelsIndex, dataPanelsIndex );
		dataPanelsIndex++;
	}
	localizationPage = new wxPanel( dataPanels, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer7->AddGrowableCol( 0, 1 );
	fgSizer7->AddGrowableRow( 0 );
	fgSizer7->AddGrowableRow( 1, 1 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	langAdd = new wxButton( localizationPage, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );

	langAdd->SetBitmap( wxArtProvider::GetBitmap( ArtIconAdd, wxART_BUTTON ) );
	bSizer8->Add( langAdd, 0, wxALL, 0 );

	langRemove = new wxButton( localizationPage, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );

	langRemove->SetBitmap( wxArtProvider::GetBitmap( ArtIconRemove, wxART_BUTTON ) );
	bSizer8->Add( langRemove, 0, wxALL, 0 );


	fgSizer7->Add( bSizer8, 1, wxEXPAND, 0 );

	languageListBox = new wxListBox( localizationPage, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	fgSizer7->Add( languageListBox, 0, wxALL|wxEXPAND, 0 );


	localizationPage->SetSizer( fgSizer7 );
	localizationPage->Layout();
	fgSizer7->Fit( localizationPage );
	dataPanels->AddPage( localizationPage, wxT("Localization"), true );
	dataPanelsBitmap = wxArtProvider::GetBitmap( ArtIconLocalization, wxART_FRAME_ICON );
	if ( dataPanelsBitmap.Ok() )
	{
		dataPanelsImage = dataPanelsBitmap.ConvertToImage();
		dataPanelsImages->Add( dataPanelsImage.Scale( dataPanelsImageSize.GetWidth(), dataPanelsImageSize.GetHeight() ) );
		dataPanels->SetPageImage( dataPanelsIndex, dataPanelsIndex );
		dataPanelsIndex++;
	}

	fgSizer6->Add( dataPanels, 1, wxALL|wxEXPAND, 0 );


	m_panel8->SetSizer( fgSizer6 );
	m_panel8->Layout();
	fgSizer6->Fit( m_panel8 );
	m_panel9 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	addToScene = new wxComboBox( m_panel9, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY );
	addToScene->Append( wxT("Group") );
	addToScene->Append( wxT("Transform") );
	bSizer51->Add( addToScene, 0, wxALL, 5 );

	deleteFromScene = new wxButton( m_panel9, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( deleteFromScene, 0, wxALL, 5 );


	bSizer10->Add( bSizer51, 0, wxEXPAND, 5 );

	finalScene = new wxTreeCtrl( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_EDIT_LABELS|wxTR_HIDE_ROOT );
	bSizer10->Add( finalScene, 1, wxALL|wxEXPAND, 5 );


	m_panel9->SetSizer( bSizer10 );
	m_panel9->Layout();
	bSizer10->Fit( m_panel9 );
	m_splitter3->SplitHorizontally( m_panel8, m_panel9, 0 );
	bSizer5->Add( m_splitter3, 1, wxEXPAND, 5 );


	explorerPanel->SetSizer( bSizer5 );
	explorerPanel->Layout();
	bSizer5->Fit( explorerPanel );
	rightPane = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	rightPane->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_splitter31 = new wxSplitterWindow( rightPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter31->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::m_splitter31OnIdle ), NULL, this );
	m_splitter31->SetMinimumPaneSize( 100 );

	propertiesPanel = new wxPanel( m_splitter31, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	propertiesSizer = new wxBoxSizer( wxVERTICAL );


	propertiesPanel->SetSizer( propertiesSizer );
	propertiesPanel->Layout();
	propertiesSizer->Fit( propertiesPanel );
	renderView = new wxPanel( m_splitter31, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	renderViewSizer = new wxGridSizer( 1, 1, 0, 0 );


	renderView->SetSizer( renderViewSizer );
	renderView->Layout();
	renderViewSizer->Fit( renderView );
	m_splitter31->SplitVertically( propertiesPanel, renderView, 320 );
	bSizer12->Add( m_splitter31, 1, wxEXPAND, 5 );


	rightPane->SetSizer( bSizer12 );
	rightPane->Layout();
	bSizer12->Fit( rightPane );
	m_splitter2->SplitVertically( explorerPanel, rightPane, 300 );
	bSizer1->Add( m_splitter2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	statusBar->SetMaxSize( wxSize( 20,-1 ) );

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

	wxMenuItem* exportMenu;
	exportMenu = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Export") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( exportMenu );

	m_menubar1->Append( m_menu1, wxT("File") );

	m_menu2 = new wxMenu();
	showTransformMenu = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Show Transforms") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( showTransformMenu );
	showTransformMenu->Check( true );

	m_menubar1->Append( m_menu2, wxT("View") );

	this->SetMenuBar( m_menubar1 );

	mainToolbar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	mainToolbar->SetMaxSize( wxSize( -1,40 ) );

	navigate = mainToolbar->AddTool( wxID_ANY, wxT("Navigate To Selection"), wxArtProvider::GetBitmap( ArtToolbarNavigate, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Navigate To Selection"), wxT("Reposition camera to the selected transform node"), NULL );

	mainToolbar->Realize();


	this->Centre( wxBOTH );

	// Connect Events
	assetsTree->Connect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeBeginDrag ), NULL, this );
	assetsTree->Connect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeEndDrag ), NULL, this );
	assetsTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeSelChanged ), NULL, this );
	langAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::langAddOnButtonClick ), NULL, this );
	langRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::langRemoveOnButtonClick ), NULL, this );
	languageListBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( EditorMainWindowBase::languageListBoxOnListBox ), NULL, this );
	languageListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( EditorMainWindowBase::languageListBoxOnListBoxDClick ), NULL, this );
	addToScene->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( EditorMainWindowBase::addToSceneOnCombobox ), NULL, this );
	deleteFromScene->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::deleteFromSceneOnButtonClick ), NULL, this );
	finalScene->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( EditorMainWindowBase::finalSceneOnKeyDown ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeBeginDrag ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeBeginLabelEdit ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeEndDrag ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeEndLabelEdit ), NULL, this );
	finalScene->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeSelChanged ), NULL, this );
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::loadProjectMenuItemOnMenuSelection ), this, loadProjectMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::saveProjectMenuItemOnMenuSelection ), this, saveProjectMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::resetMenuItemOnMenuSelection ), this, resetMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::OnImport ), this, importMenuItem->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::exportMenuOnMenuSelection ), this, exportMenu->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EditorMainWindowBase::showTransformMenuOnMenuSelection ), this, showTransformMenu->GetId());
	this->Connect( navigate->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorMainWindowBase::navigateOnToolClicked ) );
}

EditorMainWindowBase::~EditorMainWindowBase()
{
	// Disconnect Events
	assetsTree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeBeginDrag ), NULL, this );
	assetsTree->Disconnect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeEndDrag ), NULL, this );
	assetsTree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::assetsTreeOnTreeSelChanged ), NULL, this );
	langAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::langAddOnButtonClick ), NULL, this );
	langRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::langRemoveOnButtonClick ), NULL, this );
	languageListBox->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( EditorMainWindowBase::languageListBoxOnListBox ), NULL, this );
	languageListBox->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( EditorMainWindowBase::languageListBoxOnListBoxDClick ), NULL, this );
	addToScene->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( EditorMainWindowBase::addToSceneOnCombobox ), NULL, this );
	deleteFromScene->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorMainWindowBase::deleteFromSceneOnButtonClick ), NULL, this );
	finalScene->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( EditorMainWindowBase::finalSceneOnKeyDown ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeBeginDrag ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeBeginLabelEdit ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeEndDrag ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeEndLabelEdit ), NULL, this );
	finalScene->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( EditorMainWindowBase::finalSceneOnTreeSelChanged ), NULL, this );
	this->Disconnect( navigate->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorMainWindowBase::navigateOnToolClicked ) );

}

TransformPanelBase::TransformPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer5->AddGrowableCol( 0, 1 );
	fgSizer5->AddGrowableCol( 1, 1 );
	fgSizer5->AddGrowableCol( 2, 1 );
	fgSizer5->AddGrowableCol( 3, 1 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	txt00 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt00->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt00, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );

	txt01 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt01->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt01, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt02 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt02->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt02, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt03 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt03->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt03, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt10 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt10->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt10, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt11 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt11->SetMinSize( wxSize( -50,-1 ) );

	fgSizer5->Add( txt11, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt12 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt12->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt12, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt13 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt13->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt13, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt20 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt20->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt20, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt21 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt21->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt21, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt22 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt22->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt22, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt23 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt23->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt23, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt30 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt30->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt30, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt31 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt31->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt31, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt32 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt32->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt32, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	txt33 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	txt33->SetMinSize( wxSize( 50,-1 ) );

	fgSizer5->Add( txt33, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );


	bSizer6->Add( fgSizer5, 0, wxALL|wxEXPAND, 0 );

	overrideCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Override Transform"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( overrideCheckBox, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 5 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableCol( 1, 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Position:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer1->Add( m_staticText1, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer4->AddGrowableCol( 0, 1 );
	fgSizer4->AddGrowableCol( 1, 1 );
	fgSizer4->AddGrowableCol( 2, 1 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	posTxt0 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	posTxt0->SetMinSize( wxSize( 50,-1 ) );

	fgSizer4->Add( posTxt0, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );

	posTxt1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	posTxt1->SetMinSize( wxSize( 50,-1 ) );

	fgSizer4->Add( posTxt1, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );

	posTxt2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	posTxt2->SetMinSize( wxSize( 50,-1 ) );

	fgSizer4->Add( posTxt2, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );


	fgSizer1->Add( fgSizer4, 1, wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer2->AddGrowableCol( 0, 1 );
	fgSizer2->AddGrowableCol( 1, 1 );
	fgSizer2->AddGrowableCol( 2, 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	scaleTxt0 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	scaleTxt0->SetMinSize( wxSize( 50,-1 ) );

	fgSizer2->Add( scaleTxt0, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );

	scaleTxt1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	scaleTxt1->SetMinSize( wxSize( 50,-1 ) );

	fgSizer2->Add( scaleTxt1, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	scaleTxt2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	scaleTxt2->SetMinSize( wxSize( 50,-1 ) );

	fgSizer2->Add( scaleTxt2, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );


	fgSizer1->Add( fgSizer2, 1, wxEXPAND, 0 );

	orientLbl = new wxStaticText( this, wxID_ANY, wxT("Orientation:"), wxDefaultPosition, wxDefaultSize, 0 );
	orientLbl->Wrap( -1 );
	fgSizer1->Add( orientLbl, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer3->AddGrowableCol( 0, 1 );
	fgSizer3->AddGrowableCol( 1, 1 );
	fgSizer3->AddGrowableCol( 2, 1 );
	fgSizer3->AddGrowableCol( 3, 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	orient0 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	orient0->SetMinSize( wxSize( 50,-1 ) );

	fgSizer3->Add( orient0, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	orient1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	orient1->SetMinSize( wxSize( 50,-1 ) );

	fgSizer3->Add( orient1, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	orient2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	orient2->SetMinSize( wxSize( 50,-1 ) );

	fgSizer3->Add( orient2, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );

	orient3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	orient3->SetMinSize( wxSize( 50,-1 ) );

	fgSizer3->Add( orient3, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 0 );


	fgSizer1->Add( fgSizer3, 1, wxEXPAND, 5 );


	bSizer6->Add( fgSizer1, 1, wxEXPAND, 0 );


	this->SetSizer( bSizer6 );
	this->Layout();

	// Connect Events
	txt00->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt01->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt02->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt03->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt10->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt11->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt12->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt13->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt20->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt21->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt22->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt23->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt30->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt31->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt32->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt33->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	overrideCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TransformPanelBase::overrideChanged ), NULL, this );
	posTxt0->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::positionChanged ), NULL, this );
	posTxt1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::positionChanged ), NULL, this );
	posTxt2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::positionChanged ), NULL, this );
	scaleTxt0->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::scaleChanged ), NULL, this );
	scaleTxt1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::scaleChanged ), NULL, this );
	scaleTxt2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::scaleChanged ), NULL, this );
	orient0->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
	orient1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
	orient2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
	orient3->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
}

TransformPanelBase::~TransformPanelBase()
{
	// Disconnect Events
	txt00->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt01->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt02->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt03->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt10->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt11->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt12->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt13->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt20->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt21->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt22->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt23->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt30->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt31->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt32->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	txt33->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::matrixValueChanged ), NULL, this );
	overrideCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TransformPanelBase::overrideChanged ), NULL, this );
	posTxt0->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::positionChanged ), NULL, this );
	posTxt1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::positionChanged ), NULL, this );
	posTxt2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::positionChanged ), NULL, this );
	scaleTxt0->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::scaleChanged ), NULL, this );
	scaleTxt1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::scaleChanged ), NULL, this );
	scaleTxt2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::scaleChanged ), NULL, this );
	orient0->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
	orient1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
	orient2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );
	orient3->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TransformPanelBase::orientationChanged ), NULL, this );

}

TextEnter::TextEnter( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 300,150 ), wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );


	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );

	textEdit = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	textEdit->SetMinSize( wxSize( 200,-1 ) );

	bSizer9->Add( textEdit, 0, wxALIGN_CENTER_HORIZONTAL, 0 );


	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	btnOk = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );

	btnOk->SetDefault();
	bSizer10->Add( btnOk, 0, wxALL, 5 );

	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( btnCancel, 0, wxALL, 5 );


	bSizer9->Add( bSizer10, 0, wxALIGN_RIGHT|wxTOP, 5 );


	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	textEdit->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TextEnter::textEditOnText ), NULL, this );
	btnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEnter::btnOkOnButtonClick ), NULL, this );
	btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEnter::btnCancelOnButtonClick ), NULL, this );
}

TextEnter::~TextEnter()
{
	// Disconnect Events
	textEdit->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TextEnter::textEditOnText ), NULL, this );
	btnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEnter::btnOkOnButtonClick ), NULL, this );
	btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextEnter::btnCancelOnButtonClick ), NULL, this );

}
