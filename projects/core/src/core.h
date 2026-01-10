#pragma once

#if defined(CORE_BUILD_DLL)
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

using lxu8 = uint8_t; // 1
using lxu16 = uint16_t; // 2
using lxu32 = uint32_t; // 4
using lxu64 = uint64_t; // 8

using lxi8 = int8_t; // 1
using lxi16 = int16_t; // 2
using lxi32 = int32_t; // 4
using lxi64 = int64_t; // 8

using lxf32 = float; // 4
using lxf64 = double; // 8

using lxbool = bool; // 1
using lxchar = char; // 1
using lxuChar = unsigned char; // 1
using lxsize = size_t; // 8