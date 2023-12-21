#include <wx/dnd.h>
#include "UICommon.h"
#include <unordered_set>
#include "../ConfigEntry.h"
#include "../TransformEntry.h"
#include "TextEnterDialog.h"
#include "EditorMainWindow.h"

EntryPath GetPath(const wxString& rootName, wxTreeCtrl* tree, wxTreeItemId id) {
    std::stack<wxString> names;

    if (!id.IsOk())
        return { rootName.ToStdString() };

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

    return { path.ToStdString() };
}

class MyTreeDropTarget : public wxTextDropTarget {
public:
    MyTreeDropTarget(const wxString& rootName, IDataModelEditor* dataModel, wxTreeCtrl* targetTreeCtrl)
        : _dataModel{ dataModel }
        , _rootName{rootName}
        , _targetTreeCtrl(targetTreeCtrl) {}

private:
    wxString _rootName;
    IDataModelEditor* _dataModel;
    wxTreeCtrl* _targetTreeCtrl;

    // Inherited via wxTextDropTarget
    bool OnDropText(wxCoord x, wxCoord y, const wxString& text) override
    {
        wxTreeItemId targetItem = _targetTreeCtrl->HitTest(wxPoint(x, y));
        if (targetItem.IsOk()) {
            auto parentPath = GetPath(_rootName, _targetTreeCtrl, targetItem);
            _dataModel->Execute(IDataModelEditor::CopyNodeCommand{ .SourcePath = text.ToStdString(), .TargetPath = parentPath });
        }
        else {
            _dataModel->Execute(IDataModelEditor::CopyNodeCommand{ .SourcePath = text.ToStdString(), .TargetPath = _rootName.ToStdString() });
        }
        return true;
    }

};

EditorMainWindow::EditorMainWindow(IDataModelEditor* dataModel, int argc, char** argv, wxWindow* parent)
    : EditorMainWindowBase(parent, -1, "Editor")
    , _dataModel{ dataModel }
{
    Maximize(true);
    wxSize size{ 16, 16 };
    _imageList = new wxImageList(size.GetWidth(), size.GetHeight(), true);
    _imageErrorIcon = _imageList->Add(wxArtProvider::GetBitmap(ArtIconError, wxART_LIST, size));
    _imageTransformImage = _imageList->Add(wxArtProvider::GetBitmap(ArtIconTransform, wxART_LIST, size));
    _imageGeometryImage = _imageList->Add(wxArtProvider::GetBitmap(ArtIconGeometry, wxART_LIST, size));
    _imageGroupImage = _imageList->Add(wxArtProvider::GetBitmap(ArtIconGroup, wxART_LIST, size));
    _imageMaterialImage = _imageList->Add(wxArtProvider::GetBitmap(ArtIconMaterial, wxART_LIST, size));
    finalScene->SetImageList(_imageList);
    assetsTree->SetImageList(_imageList);

    _transformPanel = std::make_shared<TransformPanel>(propertiesPanel);
    propertiesSizer->Add(_transformPanel.get(), 0, wxALL | wxEXPAND, 5);

    finalScene->SetDropTarget(new MyTreeDropTarget(ROOT_SCENE, _dataModel, finalScene));

    assert(_dataModel);
    _dataModel->Subscribe(this);

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
    viewerWindow->traits->debugLayer = arguments.read({ "--debug", "-d" });
    viewerWindow->traits->apiDumpLayer = arguments.read({ "--api", "-a" });

    if (arguments.errors()) {
        arguments.writeErrorMessages(std::cerr);
        return;
    }

    auto vsg_scene = _root;

    viewerWindow->initializeCallback = [&](ViewerWindow& vw, uint32_t width, uint32_t height) {
        vsg::ComputeBounds computeBounds{};
        vsg_scene->accept(computeBounds);
        vsg::dvec3 centre = (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
        double nearFarRatio = 0.001;
        _lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, 0.0, 3.5), centre,
            vsg::dvec3(0.0, 1.0, 0.0));
        auto perspective = vsg::Perspective::create(
            30.0,
            static_cast<double>(width) /
            static_cast<double>(height),
            0.1, 100.0);

        _camera = vsg::Camera::create(perspective, _lookAt, vsg::ViewportState::create(vw.window->extent2D()));

        vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(vsg_scene->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
        vw.viewer->addEventHandler(_trackball = vsg::Trackball::create(_camera, ellipsoidModel));

        auto commandGraph = vsg::createCommandGraphForView(vw.window, _camera, vsg_scene);
        vw.viewer->assignRecordAndSubmitTaskAndPresentation({ commandGraph });

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
            if (!c.second)
                continue;
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

    viewerWindow->Initialize(renderView->GetSize().GetWidth(), renderView->GetSize().GetHeight());

    this->assetsTree->AddRoot("PACKAGES");
    this->finalScene->AddRoot("SCENE");
}

void EditorMainWindow::Paint() {
    viewerWindow->PaintNow();
}

void EditorMainWindow::OnImport(wxCommandEvent& event) {
    wxFileDialog fd{ this, "Import packages", wxEmptyString, wxEmptyString, "VSG Binary (*.vsgb)|*.vsgb", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE };

    if (auto result = fd.ShowModal(); result == wxID_CANCEL)
        return;

    wxArrayString files;
    fd.GetPaths(files);

    for (auto file : files) {
        _dataModel->Execute(IDataModelEditor::ImportFileCommand{ .FilePath = file.ToStdString(), .Options = _options });
    }
}

void EditorMainWindow::Execute(const CompileCommand& cmd)
{
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        auto result = viewerWindow->viewer->compileManager->compile(cmd.Object);
        cmd.OnComplete(cmd.Object, result);
    });
}

void EditorMainWindow::Execute(const SceneCompeledNotification& cmd)
{
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        
        _root->children.clear();
        if (cmd.Root) {
            _root->addChild(cmd.Root);
        }

        viewerWindow->viewer->compileManager->compile(_root);
    });
}

void EditorMainWindow::Execute(const ModelResetNotification& cmd)
{
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

void EditorMainWindow::Execute(const LogNotification& cmd)
{
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        wxMessageBox(ErrorToString(cmd), "Error", wxICON_ERROR);
    });
}

void EditorMainWindow::Execute(const EntrySelectedNotification& cmd)
{
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _transformPanel->SetDataModel(cmd.SelectedEntry);
        _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = {ROOT_SCENE} });
    });
}

static const std::unordered_set<std::string_view> PropertiesToRecompile{
    "Orientation",
    "Position",
    "Override",
    "Scale"
};

void EditorMainWindow::Execute(const EntryPropertyChangedNotification& cmd)
{
    if (!cmd.ChangedEntry)
        return;

    if (PropertiesToRecompile.contains(cmd.Property)) {
        _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = {ROOT_SCENE} });
    }
}

void EditorMainWindow::Execute(const ConfigNotification& cmd)
{
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        _config = cmd.Config;
        UpdateConfig();
    });
}

int EditorMainWindow::GetEntryTypeImage(EntryType type) {
    switch (type)
    {
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
    case EntryType::Config:
        break;
    default:
        break;
    }

    return _imageErrorIcon;
}

void EditorMainWindow::UpdateConfig() {
    showTransformMenu->Check(_config->GetShowTransform());
}



void EditorMainWindow::Execute(const ItemAddedNotification& cmd) {
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        wxTreeCtrl* tree = nullptr;
        if (cmd.Path.GetName() == ROOT_PACKAGES) {
            tree = assetsTree;
        }
        else if (cmd.Path.GetName() == ROOT_SCENE) {
            tree = finalScene;
        }

        if (!tree)
            return;

        auto cur = cmd.Path.GetNext();

        if (!cur.IsValid())
            return;

        wxTreeItemId parent = tree->GetRootItem();

        while (cur.GetNext().IsValid()) {

            wxTreeItemIdValue cookie;
            auto child = tree->GetFirstChild(parent, cookie);

            while (true) {

                if (!child.IsOk()) {                    
                    parent = tree->AppendItem(parent, cur.GetName(), GetEntryTypeImage(cmd.Type));
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

        if (!parent.IsOk())
            return;

        auto itemId = tree->AppendItem(parent, cur.GetName(), GetEntryTypeImage(cmd.Type));
        if (tree == finalScene) {
            tree->SelectItem(itemId, true);
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = {.Path = ROOT_SCENE } });
        }
    });
}

void EditorMainWindow::Execute(const ItemRemovedNotification& cmd)
{
    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
        wxTreeCtrl* tree = nullptr;
        if (cmd.Path.GetName() == ROOT_PACKAGES) {
            tree = assetsTree;
        }
        else if (cmd.Path.GetName() == ROOT_SCENE) {
            tree = finalScene;
        }

        if (!tree)
            return;

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
            if (!child.IsOk())
                return;

            auto text = tree->GetItemText(child);
            if (text == cur.GetName()) {
                tree->Delete(child);
                return;
            }

            child = tree->GetNextChild(parent, cookie);
        }

        _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = {.Path = ROOT_SCENE } });
    });
}

void EditorMainWindow::assetsTreeOnTreeSelChanged(wxTreeEvent& event) {
    if (reseting)
        return;

    if (auto item = event.GetItem(); !item.IsOk())
        return;
    else {
        if (assetsTree->GetItemParent(item) == assetsTree->GetRootItem())
        {
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = GetPath(ROOT_PACKAGES, assetsTree, item) });
        }
    }
}

void EditorMainWindow::finalSceneOnTreeSelChanged(wxTreeEvent& event) {
    if (reseting)
        return;

    if (auto item = event.GetItem(); !item.IsOk())
        return;
    else {
        if (finalScene->GetItemParent(item) == finalScene->GetRootItem())
        {
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = GetPath(ROOT_SCENE, finalScene, item) });
        }

        _dataModel->Execute(IDataModelEditor::SelectEntryCommand{ .Path = GetPath(ROOT_SCENE, finalScene, item) });
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
        _dataModel->Execute(IDataModelEditor::CopyEntryCommand{ .SourcePath = _oldPath, .TargetPath = newPath.Path });
    }
    else {
        _dataModel->Execute(IDataModelEditor::MoveEntryCommand{ .SourcePath = _oldPath, .TargetPath = newPath.Path });
    }
    // _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = EntryPath{ ROOT_SCENE } });
}

void EditorMainWindow::deleteFromSceneOnButtonClick(wxCommandEvent& event) {
    auto s = finalScene->GetSelection();
    if (!s.IsOk())
        return;

    auto path = GetPath(ROOT_SCENE, finalScene, s);

    _dataModel->Execute(IDataModelEditor::RemoveEntryCommand{ .Path = path });
    _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = EntryPath{ ROOT_SCENE } });
}

void EditorMainWindow::addToSceneOnCombobox(wxCommandEvent& event) {
    EntryPath path{ .Path = ROOT_SCENE };

    auto s = finalScene->GetSelection();
    if (s.IsOk()) {
        path = GetPath(ROOT_SCENE, finalScene, s);
    }

    auto type = event.GetString().ToStdString();
    _dataModel->Execute(IDataModelEditor::CreateNodeCommand{ .Path = path.Append(type), .Type = type });
}

void EditorMainWindow::navigateOnToolClicked(wxCommandEvent& event) {
    
    auto transform = _transformPanel->GetDataModel();
    
    if (!transform)
        return;

    auto m = transform->GetWorldMatrix();
    auto centre = (m * vsg::dvec4(0, 0, 0, 1)).xyz;

    vsg::ComputeBounds computeBounds{};
    auto size = 0.3;
    
    _lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, size * .5, size * .5), centre,
        vsg::dvec3(0.0, 1.0, 0.0));

    _trackball->setViewpoint(_lookAt);
}

void EditorMainWindow::loadProjectMenuItemOnMenuSelection(wxCommandEvent& event) {
    wxFileDialog fd{ this, "Load project", wxEmptyString, wxEmptyString, "Khora Scene Project (*.ksp)|*.ksp", wxFD_OPEN | wxFD_FILE_MUST_EXIST };

    if (auto result = fd.ShowModal(); result == wxID_CANCEL)
        return;

    _projectStorage = fd.GetPath().ToStdString();

    _dataModel->Execute(IDataModelEditor::ResetModelCommand{});
    _dataModel->Execute(IDataModelEditor::ImportFromFileCommand{ .Path = _projectStorage });
}

void EditorMainWindow::resetMenuItemOnMenuSelection(wxCommandEvent& event) {
    _dataModel->Execute(IDataModelEditor::ResetModelCommand{});
}

void EditorMainWindow::finalSceneOnTreeBeginLabelEdit(wxTreeEvent& event) {    
}

void EditorMainWindow::finalSceneOnTreeEndLabelEdit(wxTreeEvent& event) {
    if (event.IsEditCancelled())
        return;

    auto newName = event.GetLabel();

    auto oldPath = GetPath(ROOT_SCENE, finalScene, event.GetItem());
    auto newPath = oldPath.GetParent().Append(newName.ToStdString());

    _dataModel->Execute(IDataModelEditor::RenameEntryCommand{ .OldPath = oldPath, .NewPath = newPath });

    event.Veto();
}

void EditorMainWindow::finalSceneOnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_F2) {
        auto sel = finalScene->GetSelection();
        if (sel.IsOk()) {
            finalScene->EditLabel(sel);
        }
    }
    event.Skip();
}

void EditorMainWindow::saveProjectMenuItemOnMenuSelection(wxCommandEvent& event) {
    if (_projectStorage.empty()) {
        wxFileDialog fd{ this, "Save project", wxEmptyString, wxEmptyString, "Khora Scene Project (*.ksp)|*.ksp", wxFD_SAVE };

        if (auto result = fd.ShowModal(); result == wxID_CANCEL)
            return;

        _projectStorage = fd.GetPath().ToStdString();
    }

    _dataModel->Execute(IDataModelEditor::SaveToFileCommand{ .Path = _projectStorage });
}

void EditorMainWindow::showTransformMenuOnMenuSelection(wxCommandEvent& event) {
    _config->SetShowTransform(event.IsChecked());
    _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = { ROOT_SCENE } });
}

void EditorMainWindow::exportMenuOnMenuSelection(wxCommandEvent& event) {
    
    wxFileDialog fd{ this, "Export Final Scene", wxEmptyString, wxEmptyString, "Khora Scene Project (*.vsgb)|*.vsgb", wxFD_SAVE };

    if (auto result = fd.ShowModal(); result == wxID_CANCEL)
        return;

    auto path = fd.GetPath().ToStdString();

    _dataModel->Execute(IDataModelEditor::ExportToFileCommand{ .Path = path });
}

void EditorMainWindow::langAddOnButtonClick(wxCommandEvent& event) {
    TextEnterDialog dlg(this);
    if (auto r = dlg.ShowModal(); r == wxID_CANCEL)
        return;
    else if (r == wxID_OK) {

    }
}

void EditorMainWindow::langRemoveOnButtonClick(wxCommandEvent& event) {
    event.Skip();
}

void EditorMainWindow::languageListBoxOnListBox(wxCommandEvent& event) {
    event.Skip();
}

void EditorMainWindow::languageListBoxOnListBoxDClick(wxCommandEvent& event) {
    event.Skip();
}
