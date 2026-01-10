#pragma once

#include "lxglcore.h"

namespace LXGL {
	enum class AttributeType {
		Invalid = 0,
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4
	};

	// returns gl type
	LXGL_API lxu32 AttributeGLType(AttributeType attr);
	LXGL_API lxu32 AttributeCompCount(AttributeType attr);
	LXGL_API lxu32 AttributeSize(AttributeType attr);

	struct AttributeLayout {
		lxu32 size = 0;
		lxu32 count = 0;
		AttributeType type = AttributeType::Invalid;
		lxbool normalized = 0;
		lxsize offset = 0;

		AttributeLayout(AttributeType type, lxbool normalize)
			: size(AttributeSize(type)), type(type), normalized(normalize), offset(0)
		{ }
	};

	// buffer layout
	class BufferLayout {
	private:
		std::vector<AttributeLayout> m_Attributes;
		lxu32 m_Stride = 0;

	public:
		lxu32 GetStride() const { return m_Stride; }

		auto begin() { return m_Attributes.begin(); }
		auto end() { return m_Attributes.end(); }
		auto begin() const { return m_Attributes.begin(); }
		auto end() const { return m_Attributes.end(); }

		void AddAttribute(AttributeLayout& attribute_layout) {
			attribute_layout.count = AttributeCompCount(attribute_layout.type);
			attribute_layout.offset = m_Stride;
			m_Stride += attribute_layout.size;
			m_Attributes.push_back(attribute_layout);
		}

		void ClearAttributes() {
			m_Attributes.clear();
		}

	};	
}