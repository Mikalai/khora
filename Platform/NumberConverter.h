#pragma once

#include <cstdint>

template<typename U, typename T>
constexpr U As(T v) {	
	return static_cast<U>(v);
}
