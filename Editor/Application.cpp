#include "Application.h"
#include "UI/EditorMainWindow.h"

#ifdef vsgXchange_FOUND
#include <vsgXchange/all.h>
#endif

wxIMPLEMENT_APP(Application);

bool Application::OnInit() {
    _work = InitThreadPool();
    _dataModel = DataModel::Create(_io_context);
    mainWindow = new EditorMainWindow(_dataModel.get(), argc, argv, nullptr);
    mainWindow->Show(true);

    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(Application::OnIdle));    

    return true;
}

int Application::OnExit() {
    _work.reset();
    return 0;
}

void Application::OnIdle(wxIdleEvent &WXUNUSED(evt)) {
    mainWindow->Paint();
}

std::shared_ptr<boost::asio::io_context::work> Application::InitThreadPool() {

    auto work = std::make_shared<boost::asio::io_context::work>(_io_context);

    for (auto i = 0; i < std::thread::hardware_concurrency(); ++i) {
        _threads.create_thread([&]() {
            _io_context.run();
            });
    }

    return work;
}
