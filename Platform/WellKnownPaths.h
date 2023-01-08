#pragma once

#include <Platform/Path.h>

class WellKnownPaths {
public:
	static void Init();
	static Path GetConfigFilePath();
	static Path GetDataFolder();
	static Path GetLogFilePath();
};