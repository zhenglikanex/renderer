#include "IndexGpuBuffer.h"

namespace aurora
{
	IndexGpuBuffer::IndexGpuBuffer(IndexType index_type, uint32_t index_count, const void* data)
		: index_type_(index_type)
		, index_size_(IndexSize(index_type_))
		, index_count_(index_count)
		, gpu_buffer_(GL_ELEMENT_ARRAY_BUFFER, index_size_ * index_count_, GL_STATIC_DRAW, data)
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