#ifndef INDEXGPUBUFFER_H_
#define INDEXGPUBUFFER_H_

#include "VertexTypes.h"
#include "GpuBuffer.h"

namespace aurora
{
	class IndexGpuBuffer
	{
	public:
		IndexGpuBuffer(IndexType index_type, uint32_t index_count,const void* data);
		
		void Bind();
		void UnBind();

		GLuint id() const { return gpu_buffer_.id(); }
		IndexType index_type() const { return index_type_; }
		uint32_t index_size() const { return index_size_; }
		uint32_t index_count() const { return index_count_; }
	private:
		IndexType index_type_;
		uint32_t index_size_;
		uint32_t index_count_;
		GpuBuffer gpu_buffer_;
	};
}

#endif
