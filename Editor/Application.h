#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/thread.hpp>

#include <State/Interface.h>
#include <Fonts/Interface.h>

#include "UI/EditorMainWindow.h"

class Application : public wxApp {
public:
  virtual bool OnInit() override;
  virtual int OnExit() override;

  void OnIdle(wxIdleEvent &evt);

  std::unique_ptr<boost::asio::io_context::work> InitThreadPool();
  Vandrouka::Ref<Vandrouka::Fonts::ISystemFonts> GetFonts() { return _fonts; }

  static Vandrouka::Ref<Vandrouka::Fundamental::IAggregatedProcessor> CreateWxProcessor();

private:
  Vandrouka::UI::Private::EditorMainWindow *mainWindow;
  Vandrouka::Ref<Vandrouka::Fonts::ISystemFonts> _fonts;
  std::shared_ptr<boost::asio::io_context> _io_context;
  std::unique_ptr<boost::asio::io_context::work> _work;
  boost::thread_group _threads;
  Vandrouka::Ref<Vandrouka::State::IDataModel> _dataModel;
  double _accumulator{0};
  double _alpha{0.98};
  std::chrono::high_resolution_clock::time_point _last;
};
