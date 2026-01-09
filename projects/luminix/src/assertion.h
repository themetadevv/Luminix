#pragma once

#include "core.h"
#include "utils.h"
#include "application/logger/logger.h"

#if defined(LX_ENABLE_ASSERTION)
#define LX_ASSERT(X, ...) \
    do { \
        if (!(X)) { \
            LX_WARN("<----------------------------- AF_ASSERT ----------------------------->"); \
            LX_INFO("| Expression: {}", #X); \
            LX_ERROR("| Message: {}", fmt::format(__VA_ARGS__)); \
            LX_WARN("| Location: {}::{}", util::get_file_name_from_path(__FILE__), __LINE__); \
            LX_WARN("<--------------------------------------------------->"); \
            DEBUG_BREAK(); \
        } \
    } while (0)
#else
#if defined(BUILD_WITH_CONSOLE)
#define LX_ASSERT(X, ...) \
    do { \
        if (!(X)) { \
            LX_WARN("<----------------------------- AF_ASSERT ----------------------------->"); \
            LX_INFO("| Expression: {}", #X); \
            LX_ERROR("| Message: {}", fmt::format(__VA_ARGS__)); \
            LX_WARN("| Location: {}::{}", util::get_file_name_from_path(__FILE__), __LINE__); \
            LX_WARN("<--------------------------------------------------->"); \
        } \
    } while (0)
#endif
#endif


