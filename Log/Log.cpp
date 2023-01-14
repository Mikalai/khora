#include <Config.h>

#ifdef MAD_ENGINE_ENABLE_LOG

#include <cassert>
#include <thread>
#include <iostream>
#include <fmt/ostream.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <Platform/SpinLock.h>
#include <Platform/WellKnownPaths.h>
#include <Platform/ThreadId.h>
#include "Log.h"

Logger* g_logger;

void Logger::Destroy() {
	assert(g_logger != nullptr);
	delete g_logger;
	g_logger = nullptr;
}

void Logger::Init() {
	assert(g_logger == nullptr);
	g_logger = new Logger();
}

Logger::Logger()
	: _file{ fmt::output_file(WellKnownPaths::GetLogFilePath().string()) }
{}

std::string_view GetLevelName(int level) {
	switch (level)
	{
	case 0: return "Trace";
	case 1: return "Debug";
	case 2: return "Info";
	case 3: return "Warn";
	case 4: return "Error";
	case 5: return "Critical";
	default:
		return "";
	}
}
void Logger::WriteMessage(int level, std::string&& str) {
	auto now = std::time(nullptr);
	auto msg = fmt::format("{:%Y-%m-%d} {:%H:%M:%S}\t{:#x}\t{}\t{}", fmt::localtime(now), fmt::localtime(now), GetCurrentOsThreadId(), GetLevelName(level), str);
	
	SpinLockScope lock{ _lock };

	if (level == 0)
		fmt::print(fg(fmt::color::gray) | fmt::emphasis::bold, "{}\n", msg);
	else if (level == 1)
		fmt::print(fg(fmt::color::dark_gray) | fmt::emphasis::bold, "{}\n", msg);
	else if (level == 2)
		fmt::print(fg(fmt::color::white) | fmt::emphasis::bold, "{}\n", msg);
	else if (level == 3)
		fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold, "{}\n", msg);
	else if (level == 4)
		fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "{}\n", msg);
	else if (level == 5)
		fmt::print(fg(fmt::color::white) | bg(fmt::color::red) | fmt::emphasis::bold, "{}\n", msg);

	_file.print("{}\n", msg);
}
#endif
