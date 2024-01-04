#include "Application.h"

#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/dll.hpp>

#include "UI/EditorMainWindow.h"
#include "UI/UICommon.h"

#ifdef __linux__
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef vsgXchange_FOUND
#include <vsgXchange/all.h>
#endif

wxIMPLEMENT_APP(Application);

class MyProvider : public wxArtProvider {
protected:
  wxBitmap CreateBitmap(const wxArtID &id, const wxArtClient &client,
                        const wxSize &s) override {
    wxSize size = s;

    auto path = boost::dll::program_location().parent_path();

    if (id == ArtToolbarNavigate && client == wxART_TOOLBAR) {
      path = path / "Icons" / "NavigateToSelection.png";
    } else if (id == ArtIconTransform) {
      path = path / "Icons" / "TransformIcon.png";
    } else if (id == ArtIconGeometry) {
      path = path / "Icons" / "GeometryIcon.png";
    } else if (id == ArtIconGroup) {
      path = path / "Icons" / "GroupIcon.png";
    } else if (id == ArtIconMaterial) {
      path = path / "Icons" / "MaterialIcon.png";
    } else if (id == ArtIconError) {
      path = path / "Icons" / "ErrorIcon.png";
    } else if (id == ArtIconAssets) {
      path = path / "Icons" / "AssetsIcon.png";
    } else if (id == ArtIconLocalization) {
      path = path / "Icons" / "LocalizationIcon.png";
    } else if (id == ArtIconAdd) {
      path = path / "Icons" / "AddIcon.png";
    } else if (id == ArtIconRemove) {
      path = path / "Icons" / "RemoveIcon.png";
    } else if (id == ArtIconFont) {
      path = path / "Icons" / "FontIcon.png";
    }

    wxBitmap bmp;
    bmp.LoadFile(path.native(), wxBITMAP_TYPE_ANY);
    assert(bmp.IsOk());

    if (!size.IsFullySpecified() && client == wxART_BUTTON) {
      size = wxSize{16, 16};
    }

    if (size.IsFullySpecified()) {
      wxBitmap::Rescale(bmp, size);
    }

    return bmp;
  }

  // optionally override this one as well
  //   wxIconBundle CreateIconBundle(const wxArtID &id, const wxArtClient
  //   &client) {

  //   }
};

bool Application::OnInit() {
  _work = InitThreadPool();
  wxInitAllImageHandlers();
  wxArtProvider::Push(new MyProvider);

  _fonts = ISystemFonts::Create(_io_context);
  _dataModel = DataModel::Create(_fonts, _io_context);
  mainWindow = new EditorMainWindow(_dataModel.get(), _fonts.get(), nullptr);
  mainWindow->Init(argc, argv);
  mainWindow->Show(true);

  Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(Application::OnIdle));

  return true;
}

int Application::OnExit() {
  _work.reset();
  _dataModel->GetSyncContext()->Complete();
  _fonts->GetSyncContext()->Complete();
  return 0;
}

void Application::OnIdle(wxIdleEvent &evt) {
  auto now = std::chrono::high_resolution_clock::now();
  mainWindow->Paint();
  auto dt = std::chrono::high_resolution_clock::now() - _last;
  _last = now;

  auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(dt);
  _accumulator = (_alpha * seconds.count()) + (1.0 - _alpha) * _accumulator;
  mainWindow->SetTitle("Editor " + std::to_string(1.0 / _accumulator));
  evt.RequestMore(true);
  mainWindow->OnIdle();
}

static std::shared_ptr<boost::asio::io_context> g_io_context;

std::unique_ptr<boost::asio::io_context::work> Application::InitThreadPool() {
  g_io_context = _io_context = std::make_shared<boost::asio::io_context>();
  auto work = std::make_unique<boost::asio::io_context::work>(*_io_context);

  for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
    _threads.create_thread([&]() { _io_context->run(); });
  }

  return work;
}

std::shared_ptr<boost::asio::io_context> GetIoContext() { return g_io_context; }