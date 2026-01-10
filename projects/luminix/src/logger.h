#pragma once

#include "core.h"

#include "core/logger.h"

#if defined(LX_ENABLE_ASSERTION)
	#ifdef LX_ENABLE_LOGGING
		#define LX_TRACE(...)    ::Core::Logger::GetLogger("Luminix")->trace(__VA_ARGS__)
		#define LX_INFO(...)     ::Core::Logger::GetLogger("Luminix")->info(__VA_ARGS__)
		#define LX_WARN(...)     ::Core::Logger::GetLogger("Luminix")->warn(__VA_ARGS__)
		#define LX_ERROR(...)    ::Core::Logger::GetLogger("Luminix")->error(__VA_ARGS__)
		#define LX_CRITICAL(...) ::Core::Logger::GetLogger("Luminix")->critical(__VA_ARGS__)
	#else
		#define LX_TRACE(...)
		#define LX_INFO(...)
		#define LX_WARN(...)
		#define LX_ERROR(...)
		#define LX_CRITICAL(...)
	#endif
#endif // #endif (LX_ENABLE_ASSERTION)