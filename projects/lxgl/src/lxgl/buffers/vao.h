#pragma once

#include "lxglcore.h"

#include "vbo.h"
#include "ebo.h"

namespace LXGL {
	class LXGL_API VertexArray {
	private:
		lxu32 m_RendererID = 0;
		lxu32 m_VertexAttributeIndex = 0;

		std::vector<Ref<VertexBuffer>> m_VertexBuffers = {};

	public:
		VertexArray();
		~VertexArray();

		void AddVertexBuffer(const Ref<VertexBuffer>& vbo);
		void SetElementBuffer(const Ref<ElementBuffer>& ebo);

		void Bind() const;
		void Unbind() const;
	};
}