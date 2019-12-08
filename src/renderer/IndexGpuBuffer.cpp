#include "IndexGpuBuffer.h"

namespace aurora
{
	IndexGpuBuffer::IndexGpuBuffer(IndexType index_type,uint32_t index_size, uint32_t index_num, const void* data)
		: GpuBuffer(GL_ELEMENT_ARRAY_BUFFER, index_size * index_num, GL_STATIC_DRAW, data)
		, index_type_(index_type)
		, index_size_(index_size)
		, index_num_(index_num)
		
	{

	}
}