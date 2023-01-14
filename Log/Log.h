#pragma once

#include <Config.h>
#include <Log/LogMessageFormatter.h>

#ifdef MAD_ENGINE_ENABLE_LOG

#ifdef MAD_ENGINE_USE_FMT

#ifdef __linux__
#define FMT_HEADER_ONLY
#endif 

#include <fmt/core.h>
#include <fmt/os.h>
#include <Platform/SpinLock.h>

class Logger {
public:

	Logger();

	template<typename... T>
	void Log(int level, fmt::format_string<T...> format, T&&... args) {		
		auto str = fmt::format(std::move(format), std::forward<T>(args)...);
		WriteMessage(level, std::move(str));
	}

	static void Init();
	static void Destroy();

private:
	void WriteMessage(int level, std::string&& str);

private:
	SpinLock _lock;
	decltype(fmt::output_file("")) _file;
};

#endif

class GlobalLoggerScope {
public:
	GlobalLoggerScope() {
		Logger::Init();
	}

	~GlobalLoggerScope() {
		Logger::Destroy();
	}
};

extern Logger* g_logger;

#define INIT_LOGGER() GlobalLoggerScope g_logger_scope

#if 0 >= MAD_ENGINE_LOG_LEVEL 
#define TRACE(X, ...) { g_logger->Log(0, X, ##__VA_ARGS__); }
#else
#define TRACE(X, ...)
#endif

#if 1 >= MAD_ENGINE_LOG_LEVEL 
#define DEBUG(X, ...) { g_logger->Log(1, X, ##__VA_ARGS__); }
#else
#define DEBUG(X, ...)
#endif

#if 2 >= MAD_ENGINE_LOG_LEVEL 
#define INFO(X, ...) { g_logger->Log(2, X, ##__VA_ARGS__); }
#else
#define INFO(X, ...)
#endif

#if 3 >= MAD_ENGINE_LOG_LEVEL 
#define WARN(X, ...) { g_logger->Log(3, X, ##__VA_ARGS__); }
#else
#define WARN(X, ...)
#endif


#if 4 >= MAD_ENGINE_LOG_LEVEL 
#define ERROR(X, ...) { g_logger->Log(4, X, ##__VA_ARGS__); }
#else
#define ERROR(X, ...)
#endif


#if 5 >= MAD_ENGINE_LOG_LEVEL 
#define CRITICAL(X, ...) { g_logger->Log(5, X, ##__VA_ARGS__); }
#else
#define CRITICAL(X, ...)
#endif

#else

#define INIT_LOGGER() {}
#define TRACE(X) {}
#define DEBUG(X) {}
#define INFO(X) {}
#define WARN(X) {}
#define ERROR(X) {}
#define CRITICAL(X) {}

#endif

