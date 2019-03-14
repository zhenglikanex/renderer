#include "IndexGpuBuffer.h"

namespace aurora
{
	IndexGpuBuffer::IndexGpuBuffer(uint32_t index_size, uint32_t index_count, const void* data)
		: gpu_buffer_(GL_ELEMENT_ARRAY_BUFFER, index_size_ * index_count_, GL_STATIC_DRAW, data)
		, index_size_(index_size)
		, index_count_(index_count)
	{

	}

	void IndexGpuBuffer::Bind()
	{
		gpu_buffer_.Bind();
	}

	void IndexGpuBuffer::UnBind()
	{
		gpu_buffer_.UnBind();
	}
}