#ifndef INDEXGPUBUFFER_H_
#define INDEXGPUBUFFER_H_

#include "GpuBuffer.h"

namespace aurora
{
	class IndexGpuBuffer
	{
	public:
		IndexGpuBuffer(uint32_t index_size, uint32_t index_count,const void* data);
		
		void Bind();
		void UnBind();

		GpuBuffer id() const { return gpu_buffer_.id(); }
		uint32_t index_size() const { return index_size_; }
		uint32_t index_count() const { return index_count_; }
	private:
		GpuBuffer gpu_buffer_;
		uint32_t index_size_;
		uint32_t index_count_;
	};
}

#endif
