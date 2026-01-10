
#include "lxglpch.h"
#include "lxgldebug.h"

#include "vbo.h"

namespace LXGL {
	VertexBuffer::VertexBuffer(lxsize size) {
		glCall(glGenBuffers(1, &m_RendererID));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::VertexBuffer(lxsize size, const void* data) {
		glCall(glGenBuffers(1, &m_RendererID));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::~VertexBuffer() {
		if (m_RendererID)
			glCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::SetData(lxsize size, const void* data) const {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::Bind() const {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}
