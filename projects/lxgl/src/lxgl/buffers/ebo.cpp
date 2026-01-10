
#include "lxglpch.h"
#include "lxgldebug.h"

#include "ebo.h"

namespace LXGL {

	ElementBuffer::ElementBuffer(lxu32 count, lxu32* indices) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(lxu32), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	ElementBuffer::~ElementBuffer() {
		if(m_RendererID)
			glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_RendererID);
	}

	void ElementBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void ElementBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
