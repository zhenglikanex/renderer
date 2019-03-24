#ifndef VERTEX_TYPES_H_
#define VERTEX_TYPES_H_

#include <cstdint>

#include "glm/glm.hpp"

#include "glSupport.h"

namespace aurora
{
	template<GLuint Index, GLint Num, GLenum Type, GLboolean Normalized>
	class MakeVertexAttribFormat
	{
	public:
		static const uint32_t Value = Index << 20 | Num << 17 | Type << 1 | Normalized;
	};

	enum VertexAttribFormat : uint32_t
	{
		kPosition = MakeVertexAttribFormat<0, 3, GL_FLOAT, GL_FALSE>::Value,
		kNoraml = MakeVertexAttribFormat<1, 3, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords0 = MakeVertexAttribFormat<2, 2, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords1 = MakeVertexAttribFormat<3, 2, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords2 = MakeVertexAttribFormat<4, 2, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords3 = MakeVertexAttribFormat<5, 2, GL_FLOAT, GL_FALSE>::Value,
		kTangent = MakeVertexAttribFormat<6, 3, GL_FLOAT, GL_FALSE>::Value,
		kBitangent = MakeVertexAttribFormat<7, 3, GL_FLOAT, GL_FALSE>::Value,
		kPosition2D = MakeVertexAttribFormat<8, 2, GL_FLOAT, GL_FALSE>::Value,
	};

	inline GLuint AttribIndex(VertexAttribFormat format)
	{
		return format >> 20 & 0xFFFF;
	}

	inline GLint AttribCompoentNum(VertexAttribFormat format)
	{
		return format >> 17 & 7;
	}

	inline GLenum AttribType(VertexAttribFormat format)
	{
		return format >> 1 & 0xFFFF;
	}

	inline GLboolean AttribNormalized(VertexAttribFormat format)
	{
		return format & 1;
	}

	struct V_P2_T2
	{
		glm::vec2 position;
		glm::vec2 texcoord;
	};

	struct V_P3_N3_T2
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	enum VertexType
	{
		kV_P2_T2,
		kV_P3_N3_T2,
	};

	inline size_t VertexSize(VertexType type)
	{
		switch (type)
		{
		case aurora::kV_P2_T2:
			return sizeof(V_P2_T2);
		case aurora::kV_P3_N3_T2:
			return sizeof(V_P3_N3_T2);
		default:
			return 0;
		}
	}

	enum InstanceType
	{
		kModelMatrix,
		kNormalMatrix,
	};

	enum IndexType
	{
		k16Bit,
		k32Bit
	};

	inline size_t IndexSize(IndexType type)
	{
		switch (type)
		{
		case aurora::k16Bit:
			return sizeof(uint32_t);
		case aurora::k32Bit:
			return sizeof(uint16_t);
		default:
			break;
		}
		return 0;
	}
}

#endif
