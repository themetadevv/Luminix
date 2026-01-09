#pragma once

#include "core.h"
#include "utils.h"
#include "logger.h"

#include "core/file_system.h"

#if defined(LX_ENABLE_ASSERTION)
#define LX_ASSERT(X, ...) \
    do { \
        if (!(X)) { \
            LX_WARN("<----------------------------- LX_ASSERT ----------------------------->"); \
            LX_INFO("| Expression: {}", #X); \
            LX_ERROR("| Message: {}", fmt::format(__VA_ARGS__)); \
            LX_WARN("| Location: {}::{}", Core::FileSystem::GetFileNameFromPath(__FILE__), __LINE__); \
            LX_WARN("<--------------------------------------------------->"); \
            DEBUG_BREAK(); \
        } \
    } while (0)
#else
#if (LX_CONSOLE == TRUE)
#define LX_ASSERT(X, ...) \
    do { \
        if (!(X)) { \
            LX_WARN("<----------------------------- LX_RUNTIME ----------------------------->"); \
            LX_INFO("| Expression: {}", #X); \
            LX_ERROR("| Message: {}", fmt::format(__VA_ARGS__)); \
            LX_WARN("| Location: {}::{}", Core::FileSystem::GetFileNameFromPath(__FILE__), __LINE__); \
            LX_WARN("<--------------------------------------------------->"); \
        } \
    } while (0)
#endif
#endif


