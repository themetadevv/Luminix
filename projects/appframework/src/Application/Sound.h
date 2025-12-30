#pragma once

#include "core.h"

#define AL_LIBTYPE_STATIC // must define this before including the audio library (openal), or else face the linking errors

#include <AL/al.h>
#include <AL/alc.h>

#if defined(SOUND_LIB_DEBUGGER)

// al debugger

AF_API void clear_al_error();
AF_API const char* get_al_error_enum_readable(ALenum error_code);
AF_API bool al_error(const char* conditon_name, const char* file, uint32_t line);

// alc debugger

AF_API void clear_alc_error(ALCdevice* device);
AF_API const char* get_alc_error_enum_readable(ALCenum error_code);
AF_API bool alc_error(ALCdevice* device, const char* conditon_name, const char* file, uint32_t line);

#define alCall(alFunction) \
	do { \
		clear_al_error(); \
		alFunction(); \
		if((al_error(#alFunction, __FILE__, __LINE__))) { \
			DEBUG_BREAK();  \
		} \
	} while(0)

#define alcCall(device, alcFunction) \
	do { \
		clear_alc_error(); \
		alcFunction(); \
		if((alc_error(device, #alcFunction, __FILE__, __LINE__))) { \
			DEBUG_BREAK();  \
		} \
	} while(0)

#else
#define alCall(X) X
#define alcCall(X) X
#endif

namespace af {
	
}