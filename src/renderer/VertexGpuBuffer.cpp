#include "VertexGpuBuffer.h"

namespace aurora
{
	VertexGpuBuffer::VertexGpuBuffer(uint32_t vertex_size, uint32_t vertex_count)
		:gpu_buffer_(GL_ARRAY_BUFFER,vertex_size * vertex_count_,GL_STATIC_DRAW)
		,vertex_size_(vertex_size)
		,vertex_count_(vertex_count)
	{

	}

	VertexGpuBuffer::~VertexGpuBuffer()
	{

	}

	void VertexGpuBuffer::Bind()
	{
		gpu_buffer_.Bind();
	}

	void VertexGpuBuffer::UnBind()
	{
		gpu_buffer_.UnBind();
	}
}