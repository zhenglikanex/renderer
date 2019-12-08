#ifndef VERTEX_TYPES_H_
#define VERTEX_TYPES_H_

#include <cstdint>

#include "glm/glm.hpp"

#include "glSupport.h"

namespace aurora
{

	enum VertexAttribIndex
	{
		kPosition = 0, 
		kNoraml,
		kTexCoords,
		kTangent,
		kBitangent,

		kInstanceModelMatrix1 = 9,
		kInstanceModelMatrix2 = 10,
		kInstanceModelMatrix3 = 11,
		kInstanceModelMatrix4 = 12,
		kInstanceNormalMatrix1 = 13,
		kInstanceNormalMatrix2 = 14,
		kInstanceNoramlMatrix3 = 15,
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
		glm::vec2 texcoords;
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

	struct InstanceData
	{
		glm::mat4 model_matrix;
		glm::mat3 normal_matrix;
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
			return sizeof(uint16_t);
		case aurora::k32Bit:
			return sizeof(uint32_t);
		default:
			break;
		}
		return 0;
	}
}

#endif
