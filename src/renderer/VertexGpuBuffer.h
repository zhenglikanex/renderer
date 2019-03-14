#ifndef VERTEX_GPU_BUFFER_H_
#define VERTEX_GPU_BUFFER_H_

#include "GpuBuffer.h"

namespace aurora
{
	class VertexGpuBuffer
	{
	public:
		VertexGpuBuffer(uint32_t vertex_size,uint32_t vertex_count,const void* data);
		~VertexGpuBuffer();

		void Bind();
		void UnBind();

		GLuint id() const { gpu_buffer_.id(); }
		uint32_t vertex_size() const { return vertex_size_; }
		uint32_t vertex_count() const { return vertex_count_; }
	private:
		GpuBuffer gpu_buffer_;
		uint32_t vertex_size_;
		uint32_t vertex_count_;
	};
}

#endif
