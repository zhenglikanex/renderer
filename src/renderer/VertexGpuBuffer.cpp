#include "VertexGpuBuffer.h"

namespace aurora
{
	VertexGpuBuffer::VertexGpuBuffer(VertexType vertex_type, uint32_t vertex_size, uint32_t vertex_num, const void* data)
		: GpuBuffer(GL_ARRAY_BUFFER, vertex_size*vertex_num, GL_STATIC_DRAW, data)
		, vertex_type_(vertex_type)
		, vertex_size_(vertex_size)
		, vertex_num_(vertex_num)
	{
	}

	VertexGpuBuffer::~VertexGpuBuffer()
	{

	}
}