// MadEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#ifdef _WIN32

#define NOMINMAX
#include <Windows.h>

void MadPause() {
	Sleep(0);
	// _mm_pause();
}

#endif