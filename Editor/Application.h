#pragma once

#include "UI/EditorMainWindow.h"
#include <boost/asio/io_context.hpp>
#include <boost/thread.hpp>
#include "DataModel.h"
#include "SystemFonts.h"

class Application : public wxApp {
public:
    virtual bool OnInit() override;
    virtual int OnExit() override;

    void OnIdle(wxIdleEvent &evt);

    std::shared_ptr<boost::asio::io_context::work> InitThreadPool();
    SystemFontsPtr GetFonts() { return _fonts; }

private:
    EditorMainWindow* mainWindow;
    SystemFontsPtr _fonts;
    boost::asio::io_context _io_context;    
    std::shared_ptr<boost::asio::io_context::work> _work;
    boost::thread_group _threads;
    std::shared_ptr<DataModel> _dataModel;
    double _accumulator{ 0 };
    double _alpha{ 0.98 };
    std::chrono::high_resolution_clock::time_point _last;
};
