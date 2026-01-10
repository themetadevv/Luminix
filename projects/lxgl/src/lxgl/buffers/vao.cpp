
#include "lxglpch.h"
#include "lxgldebug.h"
#include "vao.h"

namespace LXGL {
	VertexArray::VertexArray() {
		glCall(glGenVertexArrays(1, &m_RendererID));
	}

	VertexArray::~VertexArray() {
		glCall(glBindVertexArray(0));
		m_VertexBuffers.clear();
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vbo) {
		Bind();
		vbo->Bind();

		const auto& vertex_buffer_data_layout = vbo->GetLayout();
		for (const auto& element : vertex_buffer_data_layout) {
			switch (element.type) {
				case AttributeType::Invalid:
					LXGL_ASSERT(false, "Invalid! Attribute Type, Returning GL_NONE (0)"); break;

				case AttributeType::Int:
				case AttributeType::Int2:
				case AttributeType::Int3:
				case AttributeType::Int4:
				{
					glCall(glEnableVertexAttribArray(m_VertexAttributeIndex));
					glCall(glVertexAttribIPointer(
						m_VertexAttributeIndex,
						element.count, AttributeGLType(element.type),
						vertex_buffer_data_layout.GetStride(), (void*)element.offset
					));
					m_VertexAttributeIndex++;
					break;
				}

				case AttributeType::Float:
				case AttributeType::Float2:
				case AttributeType::Float3:
				case AttributeType::Float4:
				{
					glCall(glEnableVertexAttribArray(m_VertexAttributeIndex));
					glCall(glVertexAttribPointer(
						m_VertexAttributeIndex,
						element.count, AttributeGLType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						vertex_buffer_data_layout.GetStride(), (void*)element.offset
					));
					m_VertexAttributeIndex++;
					break;
				}
			}
		}

		auto it = std::find(m_VertexBuffers.begin(), m_VertexBuffers.end(), vbo);
		if (it == m_VertexBuffers.end()) {
			m_VertexBuffers.push_back(vbo);
		}
	}

	void VertexArray::SetElementBuffer(const Ref<ElementBuffer>& ebo) {
		Bind();
		ebo->Bind();
	}

	void VertexArray::Bind() const {
		glCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const {
		glCall(glBindVertexArray(0));
	}

}