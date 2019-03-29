#include "VertexGpuBuffer.h"

namespace aurora
{
	VertexGpuBuffer::VertexGpuBuffer(VertexType vertex_type, uint32_t vertex_num,const void* data)
		:  vertex_type_(vertex_type)
		, vertex_size_(VertexSize(vertex_type))
		, vertex_num_(vertex_num)
		, GpuBuffer(GL_ARRAY_BUFFER,vertex_size_*vertex_num_,GL_STATIC_DRAW,data)
	{
	}

	VertexGpuBuffer::~VertexGpuBuffer()
	{

	}
}