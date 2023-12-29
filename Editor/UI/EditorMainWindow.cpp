#include "EditorMainWindow.h"

#include <wx/dnd.h>
#include <wx/fontdlg.h>

#include <boost/algorithm/string.hpp>
#include <unordered_set>

#include "../Application.h"
#include "../ConfigEntry.h"
#include "../TransformEntry.h"
#include "TextEnterDialog.h"
#include "UICommon.h"

EntryPath GetPath(const wxString& rootName, wxTreeCtrl* tree, wxTreeItemId id) {
    std::stack<wxString> names;

    if (!id.IsOk()) return {rootName.ToStdString()};

    while (id != tree->GetRootItem()) {
        auto text = tree->GetItemText(id);
        names.push(text);
        id = tree->GetItemParent(id);
    }

    names.push(rootName);

    wxString path;

    while (!names.empty()) {
        path.append(names.top());
        names.pop();
        if (!names.empty()) {
            path.append("/");
        }
    }

    return {path.ToStdString()};
}

class MyTreeDropTarget : public wxTextDropTarget {
   public:
    MyTreeDropTarget(const wxString& rootName, IDataModelEditor* dataModel,
                     wxTreeCtrl* targetTreeCtrl)
        : _dataModel{dataModel},
          _rootName{rootName},
          _targetTreeCtrl(targetTreeCtrl) {}

   private:
    IDataModelEditor* _dataModel;
    wxString _rootName;
    wxTreeCtrl* _targetTreeCtrl;

    // Inherited via wxTextDropTarget
    bool OnDropText(wxCoord x, wxCoord y, const wxString& text) override {
        wxTreeItemId targetItem = _targetTreeCtrl->HitTest(wxPoint(x, y));
        if (targetItem.IsOk()) {
            auto parentPath = GetPath(_rootName, _targetTreeCtrl, targetItem);
            _dataModel->Execute(IDataModelEditor::CopyNodeCommand{
                .SourcePath = {text.ToStdString()},
                .TargetPath = {parentPath}});
        } else {
            _dataModel->Execute(IDataModelEditor::CopyNodeCommand{
                .SourcePath = {text.ToStdString()},
                .TargetPath = {_rootName.ToStdString()}});
        }
        return true;
    }
};

void EditorMainWindow::Init(int argc, char** argv) {
    _dataObserverAdapter = std::make_shared<DataModelObserverAdapter>(*this);
    _dataModelSubscription = _dataModel->Subscribe(_dataObserverAdapter);
    _systemFontsObserverAdapter =
        std::make_shared<SystemFontsObserverAdapter>(*this);
    _systemFontsSubscription =
        _systemFonts->Subscribe(_systemFontsObserverAdapter);

    Maximize(true);
    wxSize size{16, 16};
    this->dataPanels->SetSelection(0);

    this->languageListBox->AppendColumn("Languages", wxLIST_FORMAT_LEFT, 200);

    this->fontsList->AppendColumn("Font File", wxLIST_FORMAT_LEFT, 200);

    _imageList = new wxImageList(size.GetWidth(), size.GetHeight(), true);
    _imageErrorIcon = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconError, wxART_LIST, size));
    _imageTransformImage = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconTransform, wxART_LIST, size));
    _imageGeometryImage = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconGeometry, wxART_LIST, size));
    _imageGroupImage = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconGroup, wxART_LIST, size));
    _imageMaterialImage = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconMaterial, wxART_LIST, size));
    _imageLocalizedImage = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconLocalization, wxART_LIST, size));
    _imageTextImage = _imageList->Add(
        wxArtProvider::GetBitmap(ArtIconFont, wxART_LIST, size));
    _imagePlusImage =
        _imageList->Add(wxArtProvider::GetBitmap(ArtIconAdd, wxART_LIST, size));

    finalScene->SetImageList(_imageList);
    assetsTree->SetImageList(_imageList);
    languageListBox->SetImageList(_imageList, wxIMAGE_LIST_NORMAL);
    languageListBox->SetImageList(_imageList, wxIMAGE_LIST_SMALL);

    _transformPanel = std::make_shared<TransformPanel>(propertiesPanel);
    propertiesSizer->Add(_transformPanel.get(), 0, wxALL | wxEXPAND, 5);

    _textPanel = std::make_shared<TextPanel>(propertiesPanel);
    propertiesSizer->Add(_textPanel.get(), 0, wxALL | wxEXPAND, 5);

    finalScene->SetDropTarget(
        new MyTreeDropTarget(ROOT_SCENE, _dataModel, finalScene));

    assert(_dataModel);

    viewerWindow = new ViewerWindow(renderView);
    renderViewSizer->Add(viewerWindow, 0, wxALL | wxEXPAND, 5);

    vsg::CommandLine arguments(&argc, argv);

    // set up vsg::Options to pass in file paths and ReaderWriter's and other IO
    // related options to use when reading and writing files.
    _options = vsg::Options::create();
    _options->fileCache = vsg::getEnv("VSG_FILE_CACHE");
    _options->paths = vsg::getEnvPaths("VSG_FILE_PATH");

#ifdef vsgXchange_all
    // add vsgXchange's support for reading and writing 3rd party file formats
    options->add(vsgXchange::all::create());
#endif

    arguments.read(_options);

    viewerWindow->traits->windowTitle = "vsgwx viewer";
    viewerWindow->traits->debugLayer = arguments.read({"--debug", "-d"});
    viewerWindow->traits->apiDumpLayer = arguments.read({"--api", "-a"});

    if (arguments.errors()) {
        arguments.writeErrorMessages(std::cerr);
        return;
    }

    auto vsg_scene = _root;

    viewerWindow->initializeCallback = [&](ViewerWindow& vw, uint32_t width,
                                           uint32_t height) {
        vsg::ComputeBounds computeBounds{};
        vsg_scene->accept(computeBounds);
        vsg::dvec3 centre =
            (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
        _lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, 0.0, 3.5),
                                      centre, vsg::dvec3(0.0, 1.0, 0.0));
        auto perspective = vsg::Perspective::create(
            30.0, static_cast<double>(width) / static_cast<double>(height), 0.1,
            100.0);

        _camera = vsg::Camera::create(
            perspective, _lookAt,
            vsg::ViewportState::create(vw.window->extent2D()));

        vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(
            vsg_scene->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
        vw.viewer->addEventHandler(
            _trackball = vsg::Trackball::create(_camera, ellipsoidModel));

        auto commandGraph =
            vsg::createCommandGraphForView(vw.window, _camera, vsg_scene);
        vw.viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

        vw.viewer->compile();

        return true;
    };

    viewerWindow->frameCallback = [&](ViewerWindow& vw) {
        if (!vw.viewer || !vw.viewer->advanceToNextFrame()) {
            return false;
        }

        vw.viewer->handleEvents();

        vw.viewer->update();

        vw.viewer->recordAndSubmit();

        vw.viewer->present();

        bool empty = true;
        for (auto& c : _cleanup) {
            if (!c.second) continue;
            if (c.first-- <= 0) {
                c.second = {};
                empty = false;
            }
        }

        if (empty) {
            _cleanup.clear();
        }

        return true;
    };

    viewerWindow->Initialize(renderView->GetSize().GetWidth(),
                             renderView->GetSize().GetHeight());

    this->assetsTree->AddRoot("PACKAGES");
    this->finalScene->AddRoot("SCENE");
}

EditorMainWindow::EditorMainWindow(IDataModelEditor* dataModel,
                                   ISystemFonts* systemFonts, wxWindow* parent)
    : EditorMainWindowBase(parent, -1, "Editor"),
      _dataModel{dataModel},
      _systemFonts{systemFonts} {}

void EditorMainWindow::Paint() { viewerWindow->PaintNow(); }

void EditorMainWindow::importFontMenuOnMenuSelection(wxCommandEvent&) {}

void EditorMainWindow::fontSearchOnSearchButton(wxCommandEvent&) {}

void EditorMainWindow::fontSearchOnText(wxCommandEvent&) {
    _fontFilter = fontSearch->GetValue().ToStdString();
    UpdateFonts();
}

void EditorMainWindow::fontsListOnListItemSelected(wxListEvent& event) {
    if (auto selection = event.GetIndex(); selection >= 0) {
        _systemFonts->Execute(ISystemFonts::CompileFont{
            .DisplayName =
                fontsList->GetItemText(event.GetIndex()).ToStdString(),
            .State = {}});
    }
}

void EditorMainWindow::Execute(const FontCompiled& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _root->children.clear();

        if (cmd.Root) {
            _root->addChild(cmd.Root);
        }

        viewerWindow->viewer->compileManager->compile(_root);
    });
}

void EditorMainWindow::UpdateFonts() {
    fontsList->DeleteAllItems();
    int index = 0;
    for (size_t i = 0; i < _fontsCache.size(); ++i) {
        auto& e = _fontsCache[i];
        auto name = e.GetDisplayName();
        if (_fontFilter.empty() || boost::icontains(name, _fontFilter)) {
            wxListItem item;
            item.SetColumn(0);
            item.SetId(index++);
            item.SetText(name);
            fontsList->InsertItem(item);
        }
    }
    _textPanel->SetFonts(_fontsCache);
}

void EditorMainWindow::Execute(const RefreshComplete& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _fontsCache = cmd.Fonts;
        UpdateFonts();
    });
}

void EditorMainWindow::dataPanelsOnNotebookPageChanged(wxNotebookEvent&) {
    if (_systemFonts) {
        _systemFonts->Execute(ISystemFonts::Refresh{.Force = false});
    }

    // static_cast<Application*>(wxApp::GetInstance())->GetFonts()->Refresh(false,
    // [&](auto fonts) {
    //     auto allFonts = fonts->GetAllFonts();
    //     wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this,
    //     allFonts]() {
    //         this->fontsList->Clear();
    //         for (auto font : allFonts) {
    //             this->fontsList->AppendString(font.filename().string());
    //         }
    //     });
    // });
}

void EditorMainWindow::OnImport(wxCommandEvent&) {
    wxFileDialog fd{this,
                    "Import packages",
                    wxEmptyString,
                    wxEmptyString,
                    "VSG Binary (*.vsgb)|*.vsgb",
                    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE};

    if (auto result = fd.ShowModal(); result == wxID_CANCEL) return;

    wxArrayString files;
    fd.GetPaths(files);

    for (auto file : files) {
        _dataModel->Execute(IDataModelEditor::ImportFileCommand{
            .FilePath = file.ToStdString(),
            .Options = _options,
            .ProjectPath = this->_projectStorage.parent_path()});
    }
}

void EditorMainWindow::Execute(const CompileCommand& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        auto result = viewerWindow->viewer->compileManager->compile(cmd.Object);
        cmd.OnComplete(cmd.Object, result);
    });
}

void EditorMainWindow::Execute(const SceneCompeledNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _root->children.clear();
        if (cmd.Root) {
            _root->addChild(cmd.Root);
        }

        viewerWindow->viewer->compileManager->compile(_root);
    });
}

void EditorMainWindow::Execute(const ModelResetNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        reseting = true;
        assetsTree->UnselectAll();
        finalScene->UnselectAll();
        packageToId.clear();

        for (auto child : _root->children) {
            _cleanup.emplace_back(60, child);
        }

        _root->children.clear();
        assetsTree->DeleteAllItems();
        finalScene->DeleteAllItems();
        assetsTree->AddRoot("");
        finalScene->AddRoot("");
        reseting = false;
    });
}

void EditorMainWindow::Execute(const LogNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        if (_bulkOperation == 0) {
            wxMessageBox(ErrorToString(cmd), "Error", wxICON_ERROR);
        } else {
            _bulkErrors.push_back(ErrorToString(cmd));
        }
    });
}

void EditorMainWindow::Execute(const EntrySelectedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _transformPanel->SetDataModel(cmd.SelectedEntry);
        _textPanel->SetDataModel(cmd.SelectedEntry);
        propertiesSizer->Layout();
        _dataModel->Execute(
            IDataModelEditor::CompileSceneCommand{.Root = {ROOT_SCENE}});
    });
}

static const std::unordered_set<std::string_view> PropertiesToRecompile{
    "Orientation",
    "Position",
    "Override",
    "Scale",
    "Font",
    "Value",
    "Color",
    "Color.R",
    "Color.G",
    "Color.B",
    "Color.A",
    "Offset",
    "Offset.X",
    "Offset.Y",
    "Offset.Z",
    "VerticalAxis",
    "VerticalAxis.X",
    "VerticalAxis.Y",
    "VerticalAxis.Z",
    "HorizontalAxis",
    "HorizontalAxis.X",
    "HorizontalAxis.Y",
    "HorizontalAxis.Z",
    "HorizontalAlignment",
    "VerticalAlignment",
    "LineSpacing",
    "ActiveLanguage"};

void EditorMainWindow::Execute(const EntryPropertyChangedNotification& cmd) {
    if (!cmd.ChangedEntry) return;

    if (PropertiesToRecompile.contains(cmd.Property)) {
        _dataModel->Execute(
            IDataModelEditor::CompileSceneCommand{.Root = {ROOT_SCENE}});
    }
}

void EditorMainWindow::Execute(const ConfigNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _config = cmd.Config;
        UpdateConfig();
    });
}

void EditorMainWindow::Execute(const LanguageAddedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        wxListItem item;
        // item.SetColumn(0);
        // item.SetImage(_imagePlusImage);
        item.SetId(languageListBox->GetItemCount());
        item.SetText(cmd.Value);
        languageListBox->InsertItem(item);
    });
}

void EditorMainWindow::Execute(const ActiveLanguageChanged& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        auto id = languageListBox->FindItem(-1, cmd.NewLanguage);

        if (id >= 0) {
            wxListItem item;
            item.SetId(id);
            if (languageListBox->GetItem(item)) {
                item.SetImage(_imagePlusImage);
                languageListBox->SetItem(item);
            }
        }

        id = languageListBox->FindItem(-1, cmd.OldLanguage);
        if (id >= 0) {
            wxListItem item;
            item.SetId(id);
            if (languageListBox->GetItem(item)) {
                item.SetImage(-1);
                languageListBox->SetItem(item);
            }
        }
    });
}

void EditorMainWindow::Execute(const LanguageRemoveNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        if (auto index = languageListBox->FindItem(-1, cmd.Value); index < 0)
            return;
        else {
            languageListBox->DeleteItem(index);
        }
    });
}

void EditorMainWindow::Execute(const SuggestedChildrenNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        if (cmd.Context == "popup") {
            wxMenu menu;
            for (auto e : cmd.Suggestions) {
                auto item = menu.Append(wxID_ANY, e.Name);

                menu.Bind(
                    wxEVT_COMMAND_MENU_SELECTED,
                    [cmd, e, this](wxCommandEvent&) {
                        _dataModel->Execute(IDataModelEditor::CreateNodeCommand{
                            .Path = cmd.Path.Append(e.Name), .Type = e.Type});
                    },
                    item->GetId());
            }

            {
                menu.AppendSeparator();

                auto item = menu.Append(wxID_ANY, "Copy");

                menu.Bind(
                    wxEVT_COMMAND_MENU_SELECTED,
                    [cmd, this](wxCommandEvent&) {
                        auto s = finalScene->GetSelection();
                        if (!s.IsOk()) return;
                        _copyNode = GetPath(ROOT_SCENE, finalScene, s);
                    },
                    item->GetId());
            }

            if (_copyNode.IsValid()) {
                auto item = menu.Append(wxID_ANY, "Paste");

                menu.Bind(
                    wxEVT_COMMAND_MENU_SELECTED,
                    [cmd, this](wxCommandEvent&) {
                        auto s = finalScene->GetSelection();
                        if (!s.IsOk()) return;
                        auto target = GetPath(ROOT_SCENE, finalScene, s);
                        if (target.IsValid()) {
                            _dataModel->Execute(
                                IDataModelEditor::CopyEntryCommand{
                                    .SourcePath = _copyNode,
                                    .TargetPath = target});
                        }
                    },
                    item->GetId());
            }

            PopupMenu(&menu);
        }
    });
}

void EditorMainWindow::Execute(const BulkOperationStartedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter(
        [this, cmd]() { _bulkOperation++; });
}

void EditorMainWindow::Execute(const BulkOperationEndedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _bulkOperation--;
        assert(_bulkOperation >= 0);
        if (_bulkOperation == 0) {
            if (!_bulkErrors.empty()) {
                std::string bigMessage;
                for (auto& e : _bulkErrors) {
                    bigMessage.append(e);
                    bigMessage.append("\n\r");
                }
                wxMessageBox(bigMessage, "Error", wxICON_ERROR);
            }
        }
    });
}

int EditorMainWindow::GetEntryTypeImage(EntryType type) {
    switch (type) {
        case EntryType::Directory:
            break;
        case EntryType::Transform:
            return _imageTransformImage;
        case EntryType::Material:
            return _imageMaterialImage;
        case EntryType::Geometry:
            return _imageGeometryImage;
        case EntryType::Group:
            return _imageGroupImage;
        case EntryType::Localized:
            return _imageLocalizedImage;
        case EntryType::Config:
            break;
        case EntryType::Text:
            return _imageTextImage;
        default:
            break;
    }

    return _imageErrorIcon;
}

void EditorMainWindow::UpdateConfig() {
    showTransformMenu->Check(_config->GetShowTransform());
    languageListBox->DeleteAllItems();
    auto active = _config->GetActiveLanguage();
    for (auto e : _config->GetLanguages()) {
        wxListItem item;
        if (active == e) {
            item.SetImage(_imagePlusImage);
        }

        item.SetId(languageListBox->GetItemCount());
        item.SetText(e);
        languageListBox->InsertItem(item);
    }
}

void EditorMainWindow::Execute(const ItemAddedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        wxTreeCtrl* tree = nullptr;
        if (cmd.Path.GetName() == ROOT_PACKAGES) {
            tree = assetsTree;
        } else if (cmd.Path.GetName() == ROOT_SCENE) {
            tree = finalScene;
        }

        if (!tree) return;

        auto cur = cmd.Path.GetNext();

        if (!cur.IsValid()) return;

        wxTreeItemId parent = tree->GetRootItem();

        while (cur.GetNext().IsValid()) {
            wxTreeItemIdValue cookie;
            auto child = tree->GetFirstChild(parent, cookie);

            while (true) {
                if (!child.IsOk()) {
                    parent = tree->AppendItem(parent, cur.GetName(),
                                              GetEntryTypeImage(cmd.Type));
                    cur = cur.GetNext();
                    break;
                }

                auto text = tree->GetItemText(child);
                if (text == cur.GetName()) {
                    parent = child;
                    cur = cur.GetNext();
                    break;
                }

                child = tree->GetNextChild(parent, cookie);
            }
        }

        if (!parent.IsOk()) return;

        auto itemId = tree->AppendItem(parent, cur.GetName(),
                                       GetEntryTypeImage(cmd.Type));

        if (tree == finalScene) {
            tree->SelectItem(itemId, true);
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{
                .Root = {.Path = ROOT_SCENE}});
        }
    });
}

void EditorMainWindow::Execute(const ItemRemovedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        wxTreeCtrl* tree = nullptr;
        if (cmd.Path.GetName() == ROOT_PACKAGES) {
            tree = assetsTree;
        } else if (cmd.Path.GetName() == ROOT_SCENE) {
            tree = finalScene;
        }

        if (!tree) return;

        auto cur = cmd.Path.GetNext();
        wxTreeItemId parent = tree->GetRootItem();

        while (cur.GetNext().IsValid()) {
            wxTreeItemIdValue cookie;
            auto child = tree->GetFirstChild(parent, cookie);

            while (true) {
                if (!child.IsOk()) {
                    return;
                }

                auto text = tree->GetItemText(child);
                if (text == cur.GetName()) {
                    parent = child;
                    cur = cur.GetNext();
                    break;
                }

                child = tree->GetNextChild(parent, cookie);
            }
        }

        auto name = cur.GetName();

        wxTreeItemIdValue cookie;
        auto child = tree->GetFirstChild(parent, cookie);

        while (true) {
            if (!child.IsOk()) return;

            auto text = tree->GetItemText(child);
            if (text == cur.GetName()) {
                tree->Delete(child);
                return;
            }

            child = tree->GetNextChild(parent, cookie);
        }

        _dataModel->Execute(IDataModelEditor::CompileSceneCommand{
            .Root = {.Path = ROOT_SCENE}});
    });
}

void EditorMainWindow::assetsTreeOnTreeSelChanged(wxTreeEvent& event) {
    if (reseting) return;

    if (auto item = event.GetItem(); !item.IsOk())
        return;
    else {
        if (assetsTree->GetItemParent(item) == assetsTree->GetRootItem()) {
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{
                .Root = GetPath(ROOT_PACKAGES, assetsTree, item)});
        }
    }
}

void EditorMainWindow::finalSceneOnTreeSelChanged(wxTreeEvent& event) {
    if (reseting) return;

    if (auto item = event.GetItem(); !item.IsOk())
        return;
    else {
        if (finalScene->GetItemParent(item) == finalScene->GetRootItem()) {
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{
                .Root = GetPath(ROOT_SCENE, finalScene, item)});
        }

        _dataModel->Execute(IDataModelEditor::SelectEntryCommand{
            .Path = GetPath(ROOT_SCENE, finalScene, item)});
    }
}

void EditorMainWindow::assetsTreeOnTreeBeginDrag(wxTreeEvent& event) {
    auto text = GetPath(ROOT_PACKAGES, assetsTree, event.GetItem());

    wxTextDataObject tdo(text.Path);
    wxDropSource tds(tdo, assetsTree);
    tds.DoDragDrop(wxDrag_CopyOnly);
}

void EditorMainWindow::assetsTreeOnTreeEndDrag(wxTreeEvent& event) {
    event.Allow();
}

void EditorMainWindow::finalSceneOnTreeBeginDrag(wxTreeEvent& event) {
    _oldPath = GetPath(ROOT_SCENE, finalScene, event.GetItem());
    event.Allow();
}

void EditorMainWindow::finalSceneOnTreeEndDrag(wxTreeEvent& event) {
    // auto oldPath = GetPath(ROOT_SCENE, finalScene, event.GetOldItem());
    auto newPath = GetPath(ROOT_SCENE, finalScene, event.GetItem());
    if (wxGetKeyState(WXK_CONTROL)) {
        _dataModel->Execute(IDataModelEditor::CopyEntryCommand{
            .SourcePath = {_oldPath}, .TargetPath = {newPath.Path}});
    } else {
        _dataModel->Execute(IDataModelEditor::MoveEntryCommand{
            .SourcePath = {_oldPath}, .TargetPath = {newPath.Path}});
    }
    // _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root =
    // EntryPath{ ROOT_SCENE } });
}

void EditorMainWindow::finalSceneOnTreeItemRightClick(wxTreeEvent& event) {
    auto item = event.GetItem();
    if (item.IsOk()) {
        if (!finalScene->IsSelected(item)) {
            finalScene->SelectItem(item, true);
        }
    }

    auto path = GetPath(ROOT_SCENE, finalScene, item);

    _dataModel->Execute(IDataModelEditor::RequestSuggestedChildrenCommand{
        .Path = path, .Context = "popup"});

    event.Skip();
}

void EditorMainWindow::deleteFromSceneOnButtonClick(wxCommandEvent&) {
    auto s = finalScene->GetSelection();
    if (!s.IsOk()) return;

    auto path = GetPath(ROOT_SCENE, finalScene, s);

    _dataModel->Execute(IDataModelEditor::RemoveEntryCommand{.Path = path});
    _dataModel->Execute(
        IDataModelEditor::CompileSceneCommand{.Root = EntryPath{ROOT_SCENE}});
}

void EditorMainWindow::addToSceneOnCombobox(wxCommandEvent& event) {
    EntryPath path{.Path = ROOT_SCENE};

    auto s = finalScene->GetSelection();
    if (s.IsOk()) {
        path = GetPath(ROOT_SCENE, finalScene, s);
    }

    auto type = event.GetString().ToStdString();
    _dataModel->Execute(IDataModelEditor::CreateNodeCommand{
        .Path = path.Append(type), .Type = type});
}

void EditorMainWindow::navigateOnToolClicked(wxCommandEvent&) {
    auto transform = _transformPanel->GetDataModel();

    if (!transform) return;

    auto m = transform->GetWorldMatrix();
    auto centre = (m * vsg::dvec4(0, 0, 0, 1)).xyz;

    vsg::ComputeBounds computeBounds{};
    auto size = 0.3;

    _lookAt =
        vsg::LookAt::create(centre + vsg::dvec3(0.0, size * .5, size * .5),
                            centre, vsg::dvec3(0.0, 1.0, 0.0));

    _trackball->setViewpoint(_lookAt);
}

void EditorMainWindow::loadProjectMenuItemOnMenuSelection(wxCommandEvent&) {
    wxFileDialog fd{this,
                    "Load project",
                    wxEmptyString,
                    wxEmptyString,
                    "Khora Scene Project (*.ksp)|*.ksp",
                    wxFD_OPEN | wxFD_FILE_MUST_EXIST};

    if (auto result = fd.ShowModal(); result == wxID_CANCEL) return;

    _projectStorage = fd.GetPath().ToStdString();

    _dataModel->Execute(IDataModelEditor::ResetModelCommand{});
    _dataModel->Execute(
        IDataModelEditor::ImportFromFileCommand{.Path = _projectStorage});
}

void EditorMainWindow::resetMenuItemOnMenuSelection(wxCommandEvent&) {
    _dataModel->Execute(IDataModelEditor::ResetModelCommand{});
}

void EditorMainWindow::finalSceneOnTreeBeginLabelEdit(wxTreeEvent&) {}

void EditorMainWindow::finalSceneOnTreeEndLabelEdit(wxTreeEvent& event) {
    if (event.IsEditCancelled()) return;

    auto newName = event.GetLabel();

    auto oldPath = GetPath(ROOT_SCENE, finalScene, event.GetItem());
    auto newPath = oldPath.GetParent().Append(newName.ToStdString());

    _dataModel->Execute(IDataModelEditor::RenameEntryCommand{
        .OldPath = oldPath, .NewPath = newPath});

    event.Veto();
}

void EditorMainWindow::finalSceneOnKeyDown(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_F2) {
        auto sel = finalScene->GetSelection();
        if (sel.IsOk()) {
            finalScene->EditLabel(sel);
        }
    }
    event.Skip();
}

void EditorMainWindow::saveProjectMenuItemOnMenuSelection(wxCommandEvent&) {
    if (_projectStorage.empty()) {
        wxFileDialog fd{this,
                        "Save project",
                        wxEmptyString,
                        wxEmptyString,
                        "Khora Scene Project (*.ksp)|*.ksp",
                        wxFD_SAVE};

        if (auto result = fd.ShowModal(); result == wxID_CANCEL) return;

        _projectStorage = fd.GetPath().ToStdString();
    }

    _dataModel->Execute(
        IDataModelEditor::SaveToFileCommand{.Path = _projectStorage});
}

void EditorMainWindow::showTransformMenuOnMenuSelection(wxCommandEvent& event) {
    _config->SetShowTransform(event.IsChecked());
    _dataModel->Execute(
        IDataModelEditor::CompileSceneCommand{.Root = {ROOT_SCENE}});
}

void EditorMainWindow::exportMenuOnMenuSelection(wxCommandEvent&) {
    wxFileDialog fd{this,
                    "Export Final Scene",
                    wxEmptyString,
                    wxEmptyString,
                    "Khora Scene Project (*.vsgb)|*.vsgb",
                    wxFD_SAVE};

    if (auto result = fd.ShowModal(); result == wxID_CANCEL) return;

    auto path = fd.GetPath().ToStdString();

    _dataModel->Execute(IDataModelEditor::ExportToFileCommand{.Path = path});
}

void EditorMainWindow::langAddOnButtonClick(wxCommandEvent&) {
    TextEnterDialog dlg("Type Language Name", this);
    if (auto r = dlg.ShowModal(); r == wxID_CANCEL)
        return;
    else if (r == wxID_OK) {
        auto value = dlg.GetText();
        _dataModel->Execute(
            IDataModelEditor::AddLanguageCommand{.Value = value.ToStdString()});
    }
}

void EditorMainWindow::langRemoveOnButtonClick(wxCommandEvent&) {}

void EditorMainWindow::languageListBoxOnListBoxDClick(wxListEvent& event) {
    wxMenu menu;

    {
        auto item = menu.Append(wxID_ANY, "Set Active");

        menu.Bind(
            wxEVT_COMMAND_MENU_SELECTED,
            [event, this](wxCommandEvent&) {
                _dataModel->Execute(IDataModelEditor::SetActiveLanguageRequest{
                    .Language = event.GetLabel().ToStdString()});
            },
            item->GetId());
    }

    {
        auto item = menu.Append(wxID_ANY, "Rename");

        menu.Bind(
            wxEVT_COMMAND_MENU_SELECTED,
            [event, this](wxCommandEvent&) {
                TextEnterDialog dlg("Type Language Name", this);
                dlg.SetText(event.GetLabel().ToStdString());

                if (auto r = dlg.ShowModal(); r == wxID_CANCEL)
                    return;
                else if (r == wxID_OK) {
                    auto value = dlg.GetText();
                    _dataModel->Execute(IDataModelEditor::RenameLanguageCommand{
                        .OldValue = event.GetLabel().ToStdString(),
                        .NewValue = value.ToStdString()});
                }
            },
            item->GetId());
    }

    {
        auto item = menu.Append(wxID_ANY, "Remove");

        menu.Bind(
            wxEVT_COMMAND_MENU_SELECTED,
            [event, this](wxCommandEvent&) {
                _dataModel->Execute(IDataModelEditor::RemoveLanguageCommand{
                    .Value = event.GetLabel().ToStdString()});
            },
            item->GetId());
    }

    PopupMenu(&menu);
}

void EditorMainWindow::Execute(const LongOperationStarted& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _longOperations.insert(cmd.Operation);
        if (_longOperations.size() == 1) {
            showLongTasksBtn->SetLabel(cmd.Operation.Name);
            busyIcon->Show(true);
            showLongTasksBtn->Show(true);
            bottomBarLongTasksSizer->Layout();
            bottomBarSizer->Layout();
            Layout();
        }
    });
}

void EditorMainWindow::Execute(const LongOperationEnded& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _longOperations.erase(cmd.Operation);
        if (_longOperations.empty()) {
            showLongTasksBtn->SetLabel("");
            showLongTasksBtn->Show(false);
            busyIcon->Show(false);
        } else {
            auto op = *_longOperations.begin();
            showLongTasksBtn->SetLabel(op.Name);
        }

        bottomBarLongTasksSizer->Layout();
        bottomBarSizer->Layout();
        Layout();
    });
}

void EditorMainWindow::OnIdle() {
    if (busyIcon->IsShown()) {
        busyIcon->SetValue((busyIcon->GetValue() + 1) % busyIcon->GetRange());
    }
}