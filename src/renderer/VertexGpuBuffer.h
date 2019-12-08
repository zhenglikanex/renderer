#ifndef VERTEX_GPU_BUFFER_H_
#define VERTEX_GPU_BUFFER_H_

#include "VertexTypes.h"
#include "GpuBuffer.h"

namespace aurora
{
	class VertexGpuBuffer : public GpuBuffer
	{
	public:
		VertexGpuBuffer(VertexType vertex_type,uint32_t vertex_size, uint32_t vertex_num,const void* data);
		~VertexGpuBuffer();

		VertexType vertex_type() const { return vertex_type_; }
		uint32_t vertex_size() const { return vertex_size_; }
		uint32_t vertex_num() const { return vertex_num_; }
	private:
		VertexType vertex_type_;
		uint32_t vertex_size_;
		uint32_t vertex_num_;
	};
}

#endif
