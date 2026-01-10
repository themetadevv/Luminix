#pragma once

#include "lxglcore.h"

#if defined(LXGL_BUILD_DLL)
	#if defined(OPENGL_DEBUG)
		void clear_gl_error();
		const char* gl_error_enum_readable(GLenum error);
		bool gl_error(const char* gl_func_cstr, const char* file_name, unsigned int line);

	#define glCall(glFunction) clear_gl_error(); \
							 glFunction; \
							 if((gl_error(#glFunction, Core::FileSystem::GetFileNameFromPath(__FILE__), __LINE__))) { LXGL_BREAK(); }
	#else
		#define glCall(glFunction) glFunction
	#endif
#endif