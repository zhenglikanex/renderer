#ifndef VERTEX_TYPES_H_
#define VERTEX_TYPES_H_

#include <cstdint>

#include "glSupport.h"

namespace aurora
{
	template<GLuint Index, GLint Size, GLenum Type,GLboolean Normalized>
	class MakeVertexAttribFormat
	{
	public:
		static const uint32_t Value = Index << 20 | Size << 17 | Type << 1;
	};

	template<uint32_t Value>
	class MakeVertexAttrib
	{
	public:
		static const GLuint Index = Value >> 20 & 0xFFFF;
		static const GLint Size = Value >> 17 & 7;
		static const GLenum Type = Value >> 1 & 0xFFFF;
		static const GLboolean Normalized = Value & 1;
	};
	
	enum VertexAttribFormat : uint32_t
	{
		kPosition	= MakeVertexAttribFormat<0, 3, GL_FLOAT, GL_FALSE>::Value,
		kNoraml		= MakeVertexAttribFormat<1, 3, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords0 = MakeVertexAttribFormat<2, 2, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords1 = MakeVertexAttribFormat<3, 2, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords2 = MakeVertexAttribFormat<4, 2, GL_FLOAT, GL_FALSE>::Value,
		kTexCoords3 = MakeVertexAttribFormat<5, 2, GL_FLOAT, GL_FALSE>::Value,
		kTangent	= MakeVertexAttribFormat<6, 3, GL_FLOAT, GL_FALSE>::Value,
		kBitangent	= MakeVertexAttribFormat<7, 3, GL_FLOAT, GL_FALSE>::Value,
	};

#define MAKE_VERTEX_FORMAT(VERTEX_ATTRIB_FORMAT) MakeVertexAttrib<VERTEX_ATTRIB_FORMAT>::Index

	enum VertexFormat
	{
		V_P3_N3_T2 =
	};
}

#endif
