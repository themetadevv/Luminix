
#include "lxglpch.h"
#include "layout.h"

namespace LXGL {
	lxu32 AttributeGLType(AttributeType attr) {
		switch (attr)
		{
			case AttributeType::Invalid: 
			{
				LXGL_ASSERT(false, "Invalid! Attribute Type, Returning GL_NONE (0)");
				return GL_NONE;
			}
				
			case AttributeType::Int:
			case AttributeType::Int2:
			case AttributeType::Int3:
			case AttributeType::Int4:
				return GL_INT;

			case AttributeType::Float:
			case AttributeType::Float2:
			case AttributeType::Float3:
			case AttributeType::Float4:
				return GL_FLOAT;
		}
	}

	lxu32 AttributeCompCount(AttributeType attr) {
		switch (attr)
		{
			case AttributeType::Invalid:
			{
				LXGL_ASSERT(false, "Invalid! Attribute Type, Returning GL_NONE (0)");
				return GL_NONE;
			}

			case AttributeType::Int:
			case AttributeType::Float:
			{
				return 1;
			}

			case AttributeType::Int2:
			case AttributeType::Float2:
			{
				return 2;
			}

			case AttributeType::Int3:
			case AttributeType::Float3:
			{
				return 3;
			}

			case AttributeType::Int4:
			case AttributeType::Float4:
			{
				return 4;
			}	
		}
	}

	lxu32 AttributeSize(AttributeType attr) {
		switch (attr)
		{
		case AttributeType::Invalid:
		{
			LXGL_ASSERT(false, "Invalid! Attribute Type, Returning GL_NONE (0)");
			return GL_NONE;
		}

		case AttributeType::Int:
		case AttributeType::Float:
		{
			return 4;
		}

		case AttributeType::Int2:
		case AttributeType::Float2:
		{
			return 4 * 2;
		}

		case AttributeType::Int3:
		case AttributeType::Float3:
		{
			return 4 * 3;	
		}

		case AttributeType::Int4:
		case AttributeType::Float4:
		{
			return 4 * 4;
		}
		}
	}

}