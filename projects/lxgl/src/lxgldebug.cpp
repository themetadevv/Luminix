
#include "lxglpch.h"
#include "lxgldebug.h"

#if defined(LXGL_BUILD_DLL)
	#if defined(OPENGL_DEBUG)
		void clear_gl_error() {
			while (glGetError() != GL_NO_ERROR);
		}

		const char* gl_error_enum_readable(GLenum error) {
			switch (error) {
			case GL_NO_ERROR:
			{
				// No error has been recorded.
				// The value of this symbolic constant is guaranteed to be 0.
				return "GL_NO_ERROR"; break;
			}

			case GL_INVALID_ENUM:
			{
				// An unacceptable value is specified for an enumerated argument. 
				// The offending command is ignored and has no other side effect than to set the error flag.
				return "GL_INVALID_ENUM"; break;
			}

			case GL_INVALID_VALUE:
			{
				// A numeric argument is out of range. 
				// The offending command is ignored and has no other side effect than to set the error flag.
				return "GL_INVALID_VALUE"; break;
			}

			case GL_INVALID_OPERATION:
			{
				// The specified operation is not allowed in the current state. 
				// The offending command is ignored and has no other side effect than to set the error flag.
				return "GL_INVALID_OPERATION"; break;
			}

			case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				// The framebuffer object is not complete. 
				// The offending command is ignored and has no other side effect than to set the error flag.
				return "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
			}

			case GL_OUT_OF_MEMORY:
			{
				// There is not enough memory left to execute the command. 
				// The state of the GL is undefined, except for the state of the error flags, after this error is recorded.
				return "GL_OUT_OF_MEMORY"; break;
			}

			case GL_STACK_UNDERFLOW:
			{
				// An attempt has been made to perform an operation that would cause an internal stack to underflow.
				return "GL_STACK_UNDERFLOW"; break;
			}

			case GL_STACK_OVERFLOW:
			{
				// An attempt has been made to perform an operation that would cause an internal stack to overflow.
				return "GL_STACK_OVERFLOW"; break;
			}
			}
		}

		bool gl_error(const char* gl_func_cstr, const char* file_name, unsigned int line) {
			while (GLenum error = glGetError()) {
				LXGL_WARN("<----------------------------- LXGL_DEBUG ----------------------------->");

				LXGL_WARN("| Function : {}", gl_func_cstr);
				LXGL_WARN("| Location : {}::{}", file_name, line);
				LXGL_ERROR("| Message : {}", gl_error_enum_readable(error));

				LXGL_WARN("<--------------------------------------------------->");

				return true;
			}

			return false;
		}
	#endif // #endif defined(GL_DEBUG)
#endif // #endif defined(LXGL_BUILD_DLL)


