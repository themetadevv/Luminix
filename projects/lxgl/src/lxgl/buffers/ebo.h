#pragma once

#include "lxglcore.h"

namespace LXGL {
	class LXGL_API ElementBuffer {
	private:
		lxu32 m_RendererID = 0;

	public:
		ElementBuffer(lxu32 count, lxu32* indices); // indices should always be unsigned integer
		~ElementBuffer();

		void Bind() const;
		void Unbind() const;
	};
}