// MadEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <cstdint>

using ThreadId = std::uint64_t;

constexpr ThreadId MakeThreadId(auto value) {
	static_assert(sizeof(ThreadId) >= sizeof(value));
	return static_cast<ThreadId>(value);
}

ThreadId GetCurrentOsThreadId();