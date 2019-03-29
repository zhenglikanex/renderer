#include "IndexGpuBuffer.h"

namespace aurora
{
	IndexGpuBuffer::IndexGpuBuffer(IndexType index_type, uint32_t index_num, const void* data)
		: index_type_(index_type)
		, index_size_(IndexSize(index_type_))
		, index_num_(index_num)
		, GpuBuffer(GL_ELEMENT_ARRAY_BUFFER, index_size_ * index_num_, GL_STATIC_DRAW, data)
	{

	}
}