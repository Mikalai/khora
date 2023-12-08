#pragma once

#include "UI/EditorMainWindow.h"
#include <boost/asio/io_context.hpp>
#include <boost/thread.hpp>
#include "DataModel.h"

class Application : public wxApp {
public:
    virtual bool OnInit() override;
    virtual int OnExit() override;

    void OnIdle(wxIdleEvent &evt);

    std::shared_ptr<boost::asio::io_context::work> InitThreadPool();

private:
    EditorMainWindow* mainWindow;
    boost::asio::io_context _io_context;    
    std::shared_ptr<boost::asio::io_context::work> _work;
    boost::thread_group _threads;
    std::shared_ptr<DataModel> _dataModel;
};
