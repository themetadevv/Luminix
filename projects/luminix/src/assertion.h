#pragma once

#include "lxcore.h"
#include "logger.h"

#include "core/file_system.h"

#if defined(LX_BUILD_DLL)
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
#endif // #endif (LX_ENABLE_ASSERTION)
