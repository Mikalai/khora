#include "Config.h"
#include <cassert>
#include <string>
#include <filesystem>
#include "WellKnownPaths.h"

Path ConfigFile;
Path DataFolder;
Path LogFile;

#ifdef MAD_ENGINE_USE_BOOST_DLL
#include <boost/dll.hpp>
#endif

#ifdef _WIN32

#include <ShlObj_core.h>

void InitWindowsPaths()
{
	PWSTR str;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &str)))
	{
		ConfigFile = str;
		ConfigFile = ConfigFile / MAD_ENGINE_COMPANY / MAD_ENGINE_PRODUCT / "config.ini";
		std::filesystem::create_directories(ConfigFile.parent_path());
		LogFile = str;
		LogFile = LogFile / MAD_ENGINE_COMPANY / MAD_ENGINE_PRODUCT / "Log" / "Log.txt";
		std::filesystem::create_directories(LogFile.parent_path());
	}
}

#elif __linux__

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void InitLinuxPaths()
{
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	ConfigFile = homedir;
	ConfigFile = ConfigFile / "." MAD_ENGINE_COMPANY / MAD_ENGINE_PRODUCT / "config.ini";
	std::filesystem::create_directories(ConfigFile.parent_path());
	LogFile = "/tmp";
	LogFile = LogFile / MAD_ENGINE_COMPANY / MAD_ENGINE_PRODUCT / "Log.txt";
	std::filesystem::create_directories(LogFile.parent_path());
}
#endif

void ValidatePaths()
{
	assert(!LogFile.empty());
	assert(!DataFolder.empty());
	assert(!ConfigFile.empty());
}

void WellKnownPaths::Init()
{
#if _WIN32
	InitWindowsPaths();
#elif __linux__
	InitLinuxPaths();
#endif

#ifdef MAD_ENGINE_USE_BOOST_DLL
	DataFolder = boost::dll::program_location().wstring();
#endif

	ValidatePaths();
}

Path WellKnownPaths::GetConfigFilePath()
{
	return ConfigFile;
}

Path WellKnownPaths::GetDataFolder()
{
	return DataFolder;
}

Path WellKnownPaths::GetLogFilePath()
{
	return LogFile;
}