#include <wx/dnd.h>
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
        auto lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, 3.5, 0.0), centre,
            vsg::dvec3(0.0, 0.0, 1.0));
        auto perspective = vsg::Perspective::create(
            30.0,
            static_cast<double>(width) /
            static_cast<double>(height),
            0.1, 100.0);

        auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(vw.window->extent2D()));

        vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(vsg_scene->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
        vw.viewer->addEventHandler(vsg::Trackball::create(camera, ellipsoidModel));

        auto commandGraph = vsg::createCommandGraphForView(vw.window, camera, vsg_scene);
        vw.viewer->assignRecordAndSubmitTaskAndPresentation({ commandGraph });

        vw.viewer->compile();

        return true;
        };

    viewerWindow->frameCallback = [](ViewerWindow& vw) {
        if (!vw.viewer || !vw.viewer->advanceToNextFrame()) {
            return false;
        }

        vw.viewer->handleEvents();

        vw.viewer->update();

        vw.viewer->recordAndSubmit();

        vw.viewer->present();

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
                    parent = tree->AppendItem(parent, cur.GetName());
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

        tree->AppendItem(parent, cur.GetName());
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
    });
}

void EditorMainWindow::assetsTreeOnTreeSelChanged(wxTreeEvent& event) {
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
    if (auto item = event.GetItem(); !item.IsOk())
        return;
    else {
        if (finalScene->GetItemParent(item) == finalScene->GetRootItem())
        {
            _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root = GetPath(ROOT_SCENE, finalScene, item) });
        }
    }
}

//void EditorMainWindow::Execute(const SetRootNodeCommand& cmd)
//{
//    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
//        assert(cmd.Node);
//        _dataModel->GetRoot()->children.clear();
//        _dataModel->GetRoot()->addChild(cmd.Node);
//        });
//}



//void EditorMainWindow::assetsTreeOnTreeBeginDrag(wxTreeEvent& event) {
//    event.Allow();
//}
//
//void EditorMainWindow::assetsTreeOnTreeEndDrag(wxTreeEvent& event) {
//    event.Allow();
//    
//}
//
//void EditorMainWindow::finalSceneOnTreeBeginDrag(wxTreeEvent& event) {
//
//}
//
//void EditorMainWindow::finalSceneOnTreeEndDrag(wxTreeEvent& event) {
//
//}

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

    _dataModel->Execute(IDataModelEditor::MoveEntryCommand{ .SourcePath = _oldPath, .TargetPath = newPath.Path });
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