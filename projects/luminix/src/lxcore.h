#pragma once

#if defined(LX_DEBUG_BUILD)

#include "core.h"

#define LX_BUILD_LIB
#define LX_API __declspec(dllexport)

#define BIT(X) (1 << X)

// Luminix Debuggers

#if defined(_MSC_VER)
	#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
	#define DEBUG_BREAK() __builtin_trap()
#else
	#include <cstdlib>
	#define DEBUG_BREAK() std::abort()
#endif

#if defined(LX_DEBUG_BUILD)
	#define LX_ENABLE_LOGGING
	#define LX_ENABLE_ASSERTION
	#define LX_SOUND_DEBUGGER
#endif

#else // #else (LX_BUILD_DLL)
	#define LX_API __declspec(dllimport)
#endif