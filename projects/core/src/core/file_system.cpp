
#include "corepch.h"
#include "file_system.h"

namespace Core {
	const char* FileSystem::GetFileNameFromPath(const char* path) {
		const char* file = path;
		for (const char* p = path; *p; ++p) {
			if (*p == '/' || *p == '\\')
				file = p + 1;
		}
		return file;
	}

}