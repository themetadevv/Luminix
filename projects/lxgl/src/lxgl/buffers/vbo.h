#pragma once

#include "lxglcore.h"
#include "layout.h"

namespace LXGL {
	class LXGL_API VertexBuffer {
	private:
		lxu32 m_RendererID = 0;
		BufferLayout m_VertexBufferLayout;

	public:
		VertexBuffer(lxsize size);
		VertexBuffer(lxsize size, const void* data);
		~VertexBuffer();

		void SetLayout(const BufferLayout& layout) { m_VertexBufferLayout = layout; }
		void SetData(lxsize size, const void* data) const;
		const BufferLayout& GetLayout() { return m_VertexBufferLayout; }

		void Bind() const;
		void Unbind() const;
	};

}

