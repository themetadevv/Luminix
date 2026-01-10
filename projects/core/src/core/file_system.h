#pragma once

#include "core.h"

namespace Core {
	class CORE_API FileSystem {
	public:
		static const char* GetFileNameFromPath(const char* path);
	};
}