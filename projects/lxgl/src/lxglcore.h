#pragma once

#include <glad/glad.h>

#if defined(LXGL_BUILD_DLL)

#include "core.h"
#include "core/logger.h"
#include "core/file_system.h"

// LXGL_API
#define LXGL_API __declspec(dllexport) // exporter

// LXGL_BREAK
    #if defined(_MSC_VER)
        #define LXGL_BREAK() __debugbreak()
    #elif defined(__GNUC__) || defined(__clang__)
        #define LXGL_BREAK() __builtin_trap()
    #else 
        #include <cstdlib>
        #define LXGL_BREAK() std::abort()
    #endif 

// LXGL_DEBUGGER
    #if defined (LXGL_DEBUG_BUILD)
        #define OPENGL_DEBUG
        #define LXGL_ENABLE_DEBUGGER
    #endif

// LXGL_LOGGING
    #if defined(LXGL_ENABLE_DEBUGGER)
        #define LXGL_TRACE(...)    ::Core::Logger::GetLogger("LXGL")->trace(__VA_ARGS__)
        #define LXGL_INFO(...)     ::Core::Logger::GetLogger("LXGL")->info(__VA_ARGS__)
        #define LXGL_WARN(...)     ::Core::Logger::GetLogger("LXGL")->warn(__VA_ARGS__)
        #define LXGL_ERROR(...)    ::Core::Logger::GetLogger("LXGL")->error(__VA_ARGS__)
        #define LXGL_CRITICAL(...) ::Core::Logger::GetLogger("LXGL")->critical(__VA_ARGS__)
    #else
        #define LXGL_TRACE(...)
        #define LXGL_INFO(...)
        #define LXGL_WARN(...)
        #define LXGL_ERROR(...)
        #define LXGL_CRITICAL(...)
    #endif

// LXGL_ASSERT
    #if defined(LXGL_ENABLE_DEBUGGER)
        #define LXGL_ASSERT(X, ...) \
            do { \
                if (!(X)) { \
                    LXGL_WARN("<----------------------------- LXGL_ASSERT ----------------------------->"); \
                    LXGL_INFO("| Expression: {}", #X); \
                    LXGL_ERROR("| Message: {}", fmt::format(__VA_ARGS__)); \
                    LXGL_WARN("| Location: {}::{}", Core::FileSystem::GetFileNameFromPath(__FILE__), __LINE__); \
                    LXGL_WARN("<--------------------------------------------------->"); \
                    LXGL_BREAK(); \
                } \
            } while (0)
    #else
        #define LXGL_ASSERT(X, ...) \
            do { \
                if (!(X)) { \
                    LXGL_WARN("<----------------------------- LXGL_RUNTIME ----------------------------->"); \
                    LXGL_INFO("| Expression: {}", #X); \
                    LXGL_ERROR("| Message: {}", fmt::format(__VA_ARGS__)); \
                    LXGL_WARN("| Location: {}::{}", Core::FileSystem::GetFileNameFromPath(__FILE__), __LINE__); \
                    LXGL_WARN("<--------------------------------------------------->"); \
                } \
            } while (0)
    #endif

#else // #else (LXGL_BUILD_DLL)
    #define LXGL_API __declspec(dllimport)
#endif // #endif (LXGL_BUILD_DLL)

