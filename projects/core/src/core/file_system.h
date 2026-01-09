#pragma once

#include "def.h"

namespace Core {
	class CORE_API FileSystem {
	public:
		static const char* GetFileNameFromPath(const char* path);
	};
}