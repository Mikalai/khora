#ifdef _WIN32

#define NOMINMAX
#include <Windows.h>

void MadPause() {
    Sleep(0);
    // _mm_pause();
}

#endif