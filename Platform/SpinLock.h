// MadEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <atomic>

#ifdef _WIN32

void MadPause();

#elif __linux__
inline void MadPause() {
	sleep(0);
}
#endif

class SpinLock {
	std::atomic_flag _atomic;
public:
	SpinLock()
		: _atomic{}
	{}

	bool TryAcquire() {
		bool alreadyLocked = _atomic.test_and_set(std::memory_order_acquire);
		return !alreadyLocked;
	}

	void Acquire() {
		while (!TryAcquire()) {
			MadPause();
		}
	}

	void Release() {
		_atomic.clear(std::memory_order_release);
	}
};

class SpinLockScope {
	SpinLock* _lock;
public:

	explicit SpinLockScope(SpinLock& lock)
		: _lock{ &lock } {
		_lock->Acquire();
	}

	~SpinLockScope() {
		_lock->Release();
	}
};

