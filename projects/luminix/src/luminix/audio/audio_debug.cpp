

#include "lxpch.h"
#include "assertion.h"
#include "audio_debug.h"

#if defined(LX_SOUND_DEBUGGER)

// AL_DEBUGGER

void clear_al_error() {
	while (alGetError() != AL_NO_ERROR);
}

const char* get_al_error_enum_readable(ALenum error_code) {
	switch (error_code) {
	case AL_INVALID_NAME:      return "AL_INVALID_NAME"; break;
	case AL_INVALID_ENUM:      return "AL_INVALID_ENUM"; break;
	case AL_OUT_OF_MEMORY:     return "AL_OUT_OF_MEMORY"; break;
	case AL_INVALID_VALUE:     return "AL_INVALID_VALUE"; break;
	case AL_INVALID_OPERATION: return "AL_INVALID_OPERATION"; break;
	}

	return "AL_NO_ERROR";
}

bool al_error(const char* conditon_name, const char* file, uint32_t line) {
	while (ALenum error_code = alGetError()) {
		LX_WARN("<----------------------------- AL_DEBUG ----------------------------->");

		LX_WARN("| Condition : {}", conditon_name);
		LX_WARN("| Location : {}::{}", file, line);
		LX_ERROR("| Message : {}", get_al_error_enum_readable(error_code));

		LX_WARN("<--------------------------------------------------->");

		return true;
	}

	return false;
}

// ALC_DEBUGGER

void clear_alc_error(ALCdevice* device) {
	while (alcGetError(device) != ALC_NO_ERROR);
}

const char* get_alc_error_enum_readable(ALCenum error_code) {
	switch (error_code) {
	case ALC_INVALID_ENUM:      return "ALC_INVALID_ENUM"; break;
	case ALC_OUT_OF_MEMORY:     return "ALC_OUT_OF_MEMORY"; break;
	case ALC_INVALID_VALUE:     return "ALC_INVALID_VALUE"; break;
	case ALC_INVALID_DEVICE:    return "ALC_INVALID_DEVICE"; break;
	case ALC_INVALID_CONTEXT:   return "ALC_INVALID_CONTEXT"; break;
	default:                    return "ALC_UNKNOWN_ERROR";
	}

	return "ALC_NO_ERROR";
}

bool alc_error(ALCdevice* device, const char* conditon_name, const char* file, uint32_t line) {
	while (ALCenum error_code = alcGetError(device)) {
		LX_WARN("<----------------------------- ALC_DEBUG ----------------------------->");
		
		LX_WARN("| Condition : {}", conditon_name);
		LX_WARN("| Location : {}::{}", file, line);
		LX_ERROR("| Message : {}", get_alc_error_enum_readable(error_code));
		
		LX_WARN("<--------------------------------------------------->");

		return true;
	}

	return false;
}

#endif