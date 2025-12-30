#pragma once

#include "core.h"
#include "utils.h"
#include "Application/Logger.h"

#if defined(ENABLE_ASSERTION)

inline bool get_error(bool condition, std::string_view assertion_failed_message, const char* condition_name, const char* file, int line) {
	if (condition)
		return true;

	AF_ERROR("Assertion failed: {}, {}, {}::{}", condition_name, assertion_failed_message, util::get_file_name_from_path(file), line);
	return false;
}

#define AF_ASSERT(X, ...) \
	do { \
		if(!(get_error(X, __VA_ARGS__, #X, __FILE__, __LINE__))) { \
			DEBUG_BREAK(); \
		} \
	} while(0)

#else
#define AF_ASSERT(X, ...) X;
#endif