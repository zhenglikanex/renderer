#ifndef VERTEX_TYPES_H_
#define VERTEX_TYPES_H_

#include <cstdint>

#include "glm/glm.hpp"

#include "glSupport.h"

namespace aurora
{

	enum VertexAttribFormat : uint32_t
	{
		kPosition = 0, 
		kNoraml,
		kTexCoords,
		kTangent,
		kBitangent,
	};

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
