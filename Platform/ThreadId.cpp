#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#endif

#include "ThreadId.h"

ThreadId GetCurrentOsThreadId() {
#ifdef _WIN32
	return MakeThreadId(GetCurrentThreadId());
#elif __linux__
	return MakeThreadId(syscall(__NR_gettid));
#endif
}