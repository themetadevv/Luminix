#pragma once

#include "glcore.h"

void clear_gl_error();
void gl_error_enum_readable();
void gl_error(const char* gl_func_cstr, const char* file_name, unsigned int line);

#define glCall(X, ...)