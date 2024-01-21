#include "EditorMainWindow.h"

#include <wx/dnd.h>
#include <wx/fontdlg.h>

#include <boost/algorithm/string.hpp>
#include <unordered_set>

#include <Catalog/Interface/IConfigEntry.h>
#include <Catalog/Interface/ITransformEntry.h>
#include <Fonts/Module/Messages/CompileFontMessage.h>
#include <Fonts/Module/Messages/RefreshFontsMessage.h>
#include <Fundamental/Module/Observer.h>
#include <State/Interface/IDataModelState.h>
#include <State/Module/Messages/AddLanguageMessage.h>
#include <State/Module/Messages/CompileSceneMessage.h>
#include <State/Module/Messages/CopyEntryMessage.h>
#include <State/Module/Messages/CopyNodeMessage.h>
#include <State/Module/Messages/CreateNodeMessage.h>
#include <State/Module/Messages/ExportToFileMessage.h>
#include <State/Module/Messages/ImportFileMessage.h>
#include <State/Module/Messages/RenameLanguageMessage.h>
#include <State/Module/Messages/MoveEntryMessage.h>
#include <State/Module/Messages/RemoveEntryMessage.h>
#include <State/Module/Messages/ImportFromFileMessage.h>
#include <State/Module/Messages/RemoveLanguageMessage.h>
#include <State/Module/Messages/RenameEntryMessage.h>
#include <State/Module/Messages/RequestSuggestedChildrenMessage.h>
#include <State/Module/Messages/ResetModelMessage.h>
#include <State/Module/Messages/SaveToFileMessage.h>
#include <State/Module/Messages/SelectEntryMessage.h>
#include <State/Module/Messages/SetActiveLanguageMessage.h>

#include "../Application.h"
#include "Processors.h"
#include "TextEnterDialog.h"
#include "UICommon.h"

namespace Vandrouka::UI::Private {

Catalog::EntryPath GetPath(const wxString &rootName, wxTreeCtrl *tree,
                           wxTreeItemId id) {
  std::stack<wxString> names;

  if (!id.IsOk())
    return {rootName.ToStdString()};

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

void EditorMainWindow::Reset(Vandrouka::Ref<Catalog::IEntry> root) {
  // _subscriptions[""] =
  // root.Cast<IObservable>()->Subscribe(static_cast<IObserver*>(this));

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
}

void EditorMainWindow::SelectEntry(Vandrouka::Ref<Catalog::IEntry> entry) {
  _transformPanel->SetDataModel(entry);
  _textPanel->SetDataModel(entry);
  propertiesSizer->Layout();
  _dataModel->Execute(
      new State::Private::Messages::CompileSceneMessage{{State::ROOT_SCENE}});
}

class SceneTreeItemData : public wxTreeItemData {
public:
  SceneTreeItemData();
};

class MyTreeDropTarget : public wxTextDropTarget {
public:
  MyTreeDropTarget(const wxString &rootName,
                   Vandrouka::Ref<State::IDataModel> dataModel,
                   wxTreeCtrl *targetTreeCtrl)
      : _dataModel{dataModel}, _rootName{rootName},
        _targetTreeCtrl(targetTreeCtrl) {}

private:
  Vandrouka::Ref<State::IDataModel> _dataModel;
  wxString _rootName;
  wxTreeCtrl *_targetTreeCtrl;

  // Inherited via wxTextDropTarget
  bool OnDropText(wxCoord x, wxCoord y, const wxString &text) override {
    wxTreeItemId targetItem = _targetTreeCtrl->HitTest(wxPoint(x, y));
    if (targetItem.IsOk()) {
      auto parentPath = GetPath(_rootName, _targetTreeCtrl, targetItem);
      _dataModel->Execute(
          new CopyNodeMessage{{text.ToStdString()}, {parentPath}});
    } else {
      _dataModel->Execute(
          new CopyNodeMessage{{text.ToStdString()}, {_rootName.ToStdString()}});
    }
    return true;
  }
};

void EditorMainWindow::AddLanguage(std::string value) {
  wxListItem item;
  // item.SetColumn(0);
  // item.SetImage(_imagePlusImage);
  item.SetId(languageListBox->GetItemCount());
  item.SetText(value);
  languageListBox->InsertItem(item);
}

void EditorMainWindow::SetLanguageActive(std::string oldValue,
                                         std::string newValue) {
  auto id = languageListBox->FindItem(-1, newValue);

  if (id >= 0) {
    wxListItem item;
    item.SetId(id);
    if (languageListBox->GetItem(item)) {
      item.SetImage(_imagePlusImage);
      languageListBox->SetItem(item);
    }
  }

  id = languageListBox->FindItem(-1, oldValue);
  if (id >= 0) {
    wxListItem item;
    item.SetId(id);
    if (languageListBox->GetItem(item)) {
      item.SetImage(-1);
      languageListBox->SetItem(item);
    }
  }
};

void EditorMainWindow::RemoveLanguage(std::string value) {
  if (auto index = languageListBox->FindItem(-1, value); index < 0)
    return;
  else {
    languageListBox->DeleteItem(index);
  }
}

void EditorMainWindow::SaveCurrentSelectionPath() {
  auto s = finalScene->GetSelection();
  if (!s.IsOk())
    return;
  _copyNode = GetPath(State::ROOT_SCENE, finalScene, s);
}

void EditorMainWindow::PasteEntryCopy() {
  auto s = finalScene->GetSelection();
  if (!s.IsOk())
    return;
  auto target = GetPath(State::ROOT_SCENE, finalScene, s);
  if (target.IsValid()) {
    _dataModel->Execute(
        new State::Private::Messages::CopyEntryMessage{_copyNode, target});
  }
}

EditorMainWindow::EditorMainWindow(
    Vandrouka::Ref<State::IDataModel> dataModel,
    Vandrouka::Ref<Fonts::ISystemFonts> systemFonts, wxWindow *parent)
    : EditorMainWindowBase(parent, -1, "Editor"), _dataModel{dataModel},
      _systemFonts{systemFonts} {

  _observerWrapper = new Fundamental::Private::ObserverWrapper{this};
  _processor = Application::CreateWxProcessor();
  _stateWrapper = new EditorMainWindowStateWrapper{this};
  _sinkWrapper = new Fundamental::Private::MessageSinkWrapper{this};

  _systemFontsSubscription =
      this->_systemFonts.Cast<IObservable>()->Subscribe(_observerWrapper);
  _dataModelSubscription =
      this->_dataModel.Cast<IObservable>()->Subscribe(_observerWrapper);

  _processor->AddProcessor(new Processors::FontCompiledMessageProcessor());
  _processor->AddProcessor(
      new Processors::FontsRefreshCompletedMessageProcessor());
  _processor->AddProcessor(new Processors::CompileMessageProcessor());
  _processor->AddProcessor(new Processors::SceneCompeledMessageProcessor());
  _processor->AddProcessor(new Processors::ModelResetMessageProcessor());
  _processor->AddProcessor(new Processors::EntrySelectedMessageProcessor());
  _processor->AddProcessor(
      new Processors::EntryPropertyChangedMessageProcessor());
  _processor->AddProcessor(new Processors::ConfigChangedMessageProcessor());
  _processor->AddProcessor(new Processors::LanguageAddedMessageProcessor());
  _processor->AddProcessor(
      new Processors::ActiveLanguageChangedMessageProcessor());
  _processor->AddProcessor(new Processors::LanguageRemovedMessageProcessor());
  _processor->AddProcessor(new Processors::SuggestedChildrenMessageProcessor());
  _processor->AddProcessor(
      new Processors::BulkOperationStartedMessageProcessor());
  _processor->AddProcessor(
      new Processors::BulkOperationEndedMessageProcessor());
  _processor->AddProcessor(new Processors::EntryRemovedMessageProcessor());
  _processor->AddProcessor(new Processors::EntryAddedMessageProcessor());
  _processor->AddProcessor(
      new Processors::LongOperationEndedMessageProcessor());
  _processor->AddProcessor(
      new Processors::LongOperationStartedMessageProcessor());
  _processor->SetUnhandledProcessor(
      new Processors::UnhandledMessageProcessor());
}

void EditorMainWindow::Init(int argc, char **argv) {
  Maximize(true);
  wxSize size{16, 16};
  this->dataPanels->SetSelection(0);

  this->languageListBox->AppendColumn("Languages", wxLIST_FORMAT_LEFT, 200);

  this->fontsList->AppendColumn("Font File", wxLIST_FORMAT_LEFT, 200);
  this->logsList->AppendColumn("Message", wxLIST_FORMAT_LEFT, 200);

  _imageList = new wxImageList(size.GetWidth(), size.GetHeight(), true);
  _imageErrorIcon =
      _imageList->Add(wxArtProvider::GetBitmap(ArtIconError, wxART_LIST, size));
  _imageTransformImage = _imageList->Add(
      wxArtProvider::GetBitmap(ArtIconTransform, wxART_LIST, size));
  _imageGeometryImage = _imageList->Add(
      wxArtProvider::GetBitmap(ArtIconGeometry, wxART_LIST, size));
  _imageGroupImage =
      _imageList->Add(wxArtProvider::GetBitmap(ArtIconGroup, wxART_LIST, size));
  _imageMaterialImage = _imageList->Add(
      wxArtProvider::GetBitmap(ArtIconMaterial, wxART_LIST, size));
  _imageLocalizedImage = _imageList->Add(
      wxArtProvider::GetBitmap(ArtIconLocalization, wxART_LIST, size));
  _imageTextImage =
      _imageList->Add(wxArtProvider::GetBitmap(ArtIconFont, wxART_LIST, size));
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
      new MyTreeDropTarget(State::ROOT_SCENE, _dataModel, finalScene));

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

  viewerWindow->initializeCallback = [&](ViewerWindow &vw, uint32_t width,
                                         uint32_t height) {
    vsg::ComputeBounds computeBounds{};
    vsg_scene->accept(computeBounds);
    vsg::dvec3 centre =
        (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
    _lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, 0.0, 3.5), centre,
                                  vsg::dvec3(0.0, 1.0, 0.0));
    auto perspective = vsg::Perspective::create(
        30.0, static_cast<double>(width) / static_cast<double>(height), 0.1,
        100.0);

    _camera =
        vsg::Camera::create(perspective, _lookAt,
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

  viewerWindow->frameCallback = [&](ViewerWindow &vw) {
    if (!vw.viewer || !vw.viewer->advanceToNextFrame()) {
      return false;
    }

    vw.viewer->handleEvents();

    vw.viewer->update();

    vw.viewer->recordAndSubmit();

    vw.viewer->present();

    bool empty = true;
    for (auto &c : _cleanup) {
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

  viewerWindow->Initialize(renderView->GetSize().GetWidth(),
                           renderView->GetSize().GetHeight());

  this->assetsTree->AddRoot("PACKAGES");
  this->finalScene->AddRoot("SCENE");
}

void EditorMainWindow::Paint() { viewerWindow->PaintNow(); }

void EditorMainWindow::importFontMenuOnMenuSelection(wxCommandEvent &) {}

void EditorMainWindow::fontSearchOnSearchButton(wxCommandEvent &) {}

void EditorMainWindow::fontSearchOnText(wxCommandEvent &) {
  _fontFilter = fontSearch->GetValue().ToStdString();
  UpdateFonts();
}

void EditorMainWindow::fontsListOnListItemSelected(wxListEvent &event) {
  if (auto selection = event.GetIndex(); selection >= 0) {
    _systemFonts->Execute(new Fonts::Private::Messages::CompileFontMessage{
        fontsList->GetItemText(event.GetIndex()).ToStdString(), {}});
  }
}

void EditorMainWindow::UpdateFonts() {
  fontsList->DeleteAllItems();
  int index = 0;
  for (size_t i = 0; i < _fontsCache.size(); ++i) {
    auto &e = _fontsCache[i];
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

void EditorMainWindow::dataPanelsOnNotebookPageChanged(wxNotebookEvent &) {
  if (_systemFonts) {
    _systemFonts->Execute(
        new Fonts::Private::Messages::RefreshFontsMessage{false});
  }
}

void EditorMainWindow::OnImport(wxCommandEvent &) {
  wxFileDialog fd{this,
                  "Import packages",
                  wxEmptyString,
                  wxEmptyString,
                  "VSG Binary (*.vsgb)|*.vsgb",
                  wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE};

  if (auto result = fd.ShowModal(); result == wxID_CANCEL)
    return;

  wxArrayString files;
  fd.GetPaths(files);

  for (auto file : files) {
    _dataModel->Execute(new State::Private::Messages::ImportFileMessage{
        file.ToStdString(), _options, this->_projectStorage.parent_path()});
  }
}

void EditorMainWindow::OnError(Vandrouka::Ref<IError> cmd) {
  wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter([this, cmd]() {
    if (logsList->GetItemCount() < 1000) {
      wxListItem item;
      item.SetColumn(0);
      item.SetText(cmd->ToString());
      item.SetId(logsList->GetItemCount());
      logsList->InsertItem(item);
    }

    if (_bulkOperation == 0) {
      // wxMessageBox(cmd->ToString(), "Error", wxICON_ERROR);
    } else {
      _bulkErrors.push_back(cmd->ToString());
    }
  });
}

void EditorMainWindow::AddRef() {}

void EditorMainWindow::Release() {}

bool EditorMainWindow::QueryInterface(const InterfaceId &id, void **o) {
  if (o)
    *o = nullptr;
  return false;
}

void EditorMainWindow::OnNext(Vandrouka::Ref<IMessage> msg) {
  _processor->Process(_stateWrapper, msg, _sinkWrapper);
}

void EditorMainWindow::OnComplete() {}

int EditorMainWindow::GetEntryTypeImage(Catalog::EntryType type) {
  switch (type) {
  case Catalog::EntryType::Directory:
    break;
  case Catalog::EntryType::Transform:
    return _imageTransformImage;
  case Catalog::EntryType::Material:
    return _imageMaterialImage;
  case Catalog::EntryType::Geometry:
    return _imageGeometryImage;
  case Catalog::EntryType::Group:
    return _imageGroupImage;
  case Catalog::EntryType::Localized:
    return _imageLocalizedImage;
  case Catalog::EntryType::Config:
    break;
  case Catalog::EntryType::Text:
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

void EditorMainWindow::SubmitMessage(Vandrouka::Ref<IMessage> msg) {
  assert(false && "Should not be here");
}

void EditorMainWindow::SubmitError(Vandrouka::Ref<IError> msg) { OnError(msg); }

void EditorMainWindow::AddEntry(Catalog::EntryPath path,
                                Catalog::EntryType type) {
  wxTreeCtrl *tree = nullptr;
  if (path.GetName() == State::ROOT_PACKAGES) {
    tree = assetsTree;
  } else if (path.GetName() == State::ROOT_SCENE) {
    tree = finalScene;
  }

  if (!tree)
    return;

  auto cur = path.GetNext();

  if (!cur.IsValid())
    return;

  wxTreeItemId parent = tree->GetRootItem();

  while (cur.GetNext().IsValid()) {
    wxTreeItemIdValue cookie;
    auto child = tree->GetFirstChild(parent, cookie);

    while (true) {
      if (!child.IsOk()) {
        parent =
            tree->AppendItem(parent, cur.GetName(), GetEntryTypeImage(type));
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

  auto itemId =
      tree->AppendItem(parent, cur.GetName(), GetEntryTypeImage(type));

  if (tree == finalScene) {
    if (_longOperations.empty()) {
      tree->SelectItem(itemId, true);
      _dataModel->Execute(new State::Private::Messages::CompileSceneMessage{{State::ROOT_SCENE}});
    }
  }
}

void EditorMainWindow::RemoveEntry(Catalog::EntryPath path) {
  wxTreeCtrl *tree = nullptr;
  if (path.GetName() == State::ROOT_PACKAGES) {
    tree = assetsTree;
  } else if (path.GetName() == State::ROOT_SCENE) {
    tree = finalScene;
  }

  if (!tree)
    return;

  auto cur = path.GetNext();
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

  _dataModel->Execute(new State::Private::Messages::CompileSceneMessage{{State::ROOT_SCENE}});
}

void EditorMainWindow::assetsTreeOnTreeSelChanged(wxTreeEvent &event) {
  if (reseting)
    return;

  if (auto item = event.GetItem(); !item.IsOk())
    return;
  else {
    if (assetsTree->GetItemParent(item) == assetsTree->GetRootItem()) {
      _dataModel->Execute(new State::Private::Messages::CompileSceneMessage{
          GetPath(State::ROOT_PACKAGES, assetsTree, item)});
    }
  }
}

void EditorMainWindow::finalSceneOnTreeSelChanged(wxTreeEvent &event) {
  if (reseting)
    return;

  if (auto item = event.GetItem(); !item.IsOk())
    return;
  else {
    if (finalScene->GetItemParent(item) == finalScene->GetRootItem()) {
      _dataModel->Execute(new State::Private::Messages::CompileSceneMessage{
          GetPath(State::ROOT_SCENE, finalScene, item)});
    }

    _dataModel->Execute(new State::Private::Messages::SelectEntryMessage{
        GetPath(State::ROOT_SCENE, finalScene, item)});
  }
}

void EditorMainWindow::assetsTreeOnTreeBeginDrag(wxTreeEvent &event) {
  auto text = GetPath(State::ROOT_PACKAGES, assetsTree, event.GetItem());

  wxTextDataObject tdo(text.Path);
  wxDropSource tds(tdo, assetsTree);
  tds.DoDragDrop(wxDrag_CopyOnly);
}

void EditorMainWindow::assetsTreeOnTreeEndDrag(wxTreeEvent &event) {
  event.Allow();
}

void EditorMainWindow::finalSceneOnTreeBeginDrag(wxTreeEvent &event) {
  _oldPath = GetPath(State::ROOT_SCENE, finalScene, event.GetItem());
  event.Allow();
}

void EditorMainWindow::finalSceneOnTreeEndDrag(wxTreeEvent &event) {
  // auto oldPath = GetPath(ROOT_SCENE, finalScene, event.GetOldItem());
  auto newPath = GetPath(State::ROOT_SCENE, finalScene, event.GetItem());
  if (wxGetKeyState(WXK_CONTROL)) {
    _dataModel->Execute(
        new State::Private::Messages::CopyEntryMessage{{_oldPath}, {newPath.Path}});
  } else {
    _dataModel->Execute(new State::Private::Messages::MoveEntryMessage{
        {_oldPath}, {newPath.Path}});
  }
  // _dataModel->Execute(IDataModelEditor::CompileSceneCommand{ .Root =
  // EntryPath{ ROOT_SCENE } });
}

void EditorMainWindow::finalSceneOnTreeItemRightClick(wxTreeEvent &event) {
  auto item = event.GetItem();
  if (item.IsOk()) {
    if (!finalScene->IsSelected(item)) {
      finalScene->SelectItem(item, true);
    }
  }

  auto path = GetPath(State::ROOT_SCENE, finalScene, item);

  _dataModel->Execute(
      new State::Private::Messages::RequestSuggestedChildrenMessage{path,
                                                                    "popup"});

  event.Skip();
}

void EditorMainWindow::deleteFromSceneOnButtonClick(wxCommandEvent &) {
  auto s = finalScene->GetSelection();
  if (!s.IsOk())
    return;

  auto path = GetPath(State::ROOT_SCENE, finalScene, s);

  _dataModel->Execute(new State::Private::Messages::RemoveEntryMessage{path});
  _dataModel->Execute(
      new State::Private::Messages::CompileSceneMessage{{State::ROOT_SCENE}});
}

void EditorMainWindow::addToSceneOnCombobox(wxCommandEvent &event) {
  Catalog::EntryPath path{.Path = State::ROOT_SCENE};

  auto s = finalScene->GetSelection();
  if (s.IsOk()) {
    path = GetPath(State::ROOT_SCENE, finalScene, s);
  }

  auto type = event.GetString().ToStdString();
  _dataModel->Execute(
      new State::Private::Messages::CreateNodeMessage{path.Append(type), type});
}

void EditorMainWindow::navigateOnToolClicked(wxCommandEvent &) {
  auto transform = _transformPanel->GetDataModel();

  if (!transform)
    return;

  auto m = transform->GetWorldMatrix();
  auto centre = (m * vsg::dvec4(0, 0, 0, 1)).xyz;

  vsg::ComputeBounds computeBounds{};
  auto size = 0.3;

  _lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, size * .5, size * .5),
                                centre, vsg::dvec3(0.0, 1.0, 0.0));

  _trackball->setViewpoint(_lookAt);
}

void EditorMainWindow::loadProjectMenuItemOnMenuSelection(wxCommandEvent &) {
  wxFileDialog fd{this,
                  "Load project",
                  wxEmptyString,
                  wxEmptyString,
                  "Khora Scene Project (*.ksp)|*.ksp",
                  wxFD_OPEN | wxFD_FILE_MUST_EXIST};

  if (auto result = fd.ShowModal(); result == wxID_CANCEL)
    return;

  _projectStorage = fd.GetPath().ToStdString();

  _dataModel->Execute(new State::Private::Messages::ResetModelMessage{});
  _dataModel->Execute(
      new State::Private::Messages::ImportFromFileMessage{_projectStorage});
}

void EditorMainWindow::resetMenuItemOnMenuSelection(wxCommandEvent &) {
  _dataModel->Execute(new State::Private::Messages::ResetModelMessage{});
}

void EditorMainWindow::finalSceneOnTreeBeginLabelEdit(wxTreeEvent &) {}

void EditorMainWindow::finalSceneOnTreeEndLabelEdit(wxTreeEvent &event) {
  if (event.IsEditCancelled())
    return;

  auto newName = event.GetLabel();

  auto oldPath = GetPath(State::ROOT_SCENE, finalScene, event.GetItem());
  auto newPath = oldPath.GetParent().Append(newName.ToStdString());

  _dataModel->Execute(
      new State::Private::Messages::RenameEntryMessage{oldPath, newPath});

  event.Veto();
}

void EditorMainWindow::finalSceneOnKeyDown(wxKeyEvent &event) {
  if (event.GetKeyCode() == WXK_F2) {
    auto sel = finalScene->GetSelection();
    if (sel.IsOk()) {
      finalScene->EditLabel(sel);
    }
  }
  event.Skip();
}

void EditorMainWindow::saveProjectMenuItemOnMenuSelection(wxCommandEvent &) {
  if (_projectStorage.empty()) {
    wxFileDialog fd{this,
                    "Save project",
                    wxEmptyString,
                    wxEmptyString,
                    "Khora Scene Project (*.ksp)|*.ksp",
                    wxFD_SAVE};

    if (auto result = fd.ShowModal(); result == wxID_CANCEL)
      return;

    _projectStorage = fd.GetPath().ToStdString();
  }

  _dataModel->Execute(
      new State::Private::Messages::SaveToFileMessage{_projectStorage});
}

void EditorMainWindow::showTransformMenuOnMenuSelection(wxCommandEvent &event) {
  _config->SetShowTransform(event.IsChecked());
  _dataModel->Execute(
      new State::Private::Messages::CompileSceneMessage{{State::ROOT_SCENE}});
}

void EditorMainWindow::exportMenuOnMenuSelection(wxCommandEvent &) {
  wxFileDialog fd{this,
                  "Export Final Scene",
                  wxEmptyString,
                  wxEmptyString,
                  "Khora Scene Project (*.vsgb)|*.vsgb",
                  wxFD_SAVE};

  if (auto result = fd.ShowModal(); result == wxID_CANCEL)
    return;

  auto path = fd.GetPath().ToStdString();

  _dataModel->Execute(new State::Private::Messages::ExportToFileMessage{path});
}

void EditorMainWindow::langAddOnButtonClick(wxCommandEvent &) {
  TextEnterDialog dlg("Type Language Name", this);
  if (auto r = dlg.ShowModal(); r == wxID_CANCEL)
    return;
  else if (r == wxID_OK) {
    auto value = dlg.GetText();
    _dataModel->Execute(new AddLanguageMessage{value.ToStdString()});
  }
}

void EditorMainWindow::langRemoveOnButtonClick(wxCommandEvent &) {}

void EditorMainWindow::languageListBoxOnListBoxDClick(wxListEvent &event) {
  wxMenu menu;

  {
    auto item = menu.Append(wxID_ANY, "Set Active");

    menu.Bind(
        wxEVT_COMMAND_MENU_SELECTED,
        [event, this](wxCommandEvent &) {
          _dataModel->Execute(
              new State::Private::Messages::SetActiveLanguageMessage{
                  event.GetLabel().ToStdString()});
        },
        item->GetId());
  }

  {
    auto item = menu.Append(wxID_ANY, "Rename");

    menu.Bind(
        wxEVT_COMMAND_MENU_SELECTED,
        [event, this](wxCommandEvent &) {
          TextEnterDialog dlg("Type Language Name", this);
          dlg.SetText(event.GetLabel().ToStdString());

          if (auto r = dlg.ShowModal(); r == wxID_CANCEL)
            return;
          else if (r == wxID_OK) {
            auto value = dlg.GetText();
            _dataModel->Execute(
                new State::Private::Messages::RenameLanguageMessage{
                event.GetLabel().ToStdString(), value.ToStdString()});
          }
        },
        item->GetId());
  }

  {
    auto item = menu.Append(wxID_ANY, "Remove");

    menu.Bind(
        wxEVT_COMMAND_MENU_SELECTED,
        [event, this](wxCommandEvent &) {
          _dataModel->Execute(
              new State::Private::Messages::RemoveLanguageMessage{event.GetLabel().ToStdString()});
        },
        item->GetId());
  }

  PopupMenu(&menu);
}

void EditorMainWindow::BeginOperation(const LongOperation &op) {
  _longOperations.insert(op);
  if (_longOperations.size() == 1) {
    showLongTasksBtn->SetLabel(op.Name);
    busyIcon->Show(true);
    showLongTasksBtn->Show(true);
    bottomBarLongTasksSizer->Layout();
    bottomBarSizer->Layout();
    Layout();
  }
}

void EditorMainWindow::EndOperation(const LongOperation &op) {
  _longOperations.erase(op);
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
}

void EditorMainWindow::OnIdle() {
  if (busyIcon->IsShown()) {
    busyIcon->SetValue((busyIcon->GetValue() + 1) % busyIcon->GetRange());
  }
}

} // namespace Vandrouka::UI::Private
