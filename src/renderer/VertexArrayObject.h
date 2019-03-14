#ifndef VERTEX_ARRAY_OBJECT_H_
#define VERTEX_ARRAY_OBJECT_H_

#include <unordered_map>

#include "AuroraDef.h"
#include "glSupport.h"
#include "VertexTypes.h"

namespace aurora
{
	class VertexAttrib
	{
	public:
		VertexAttrib(VertexAttribFormat format,GLintptr offset,GLsizeiptr )
	private:
		VertexAttribFormat format;
		GLintptr offset;
		GLsizeiptr size;
	};
	class VertexArrayObject
	{
	public:
		VertexArrayObject(uint32_t vertex_size,uint32_t vertex_count,const void* data);
		VertexArrayObject(uint32_t vertex_size, uint32_t vertex_count,const void* vertex_data,uint32_t index_size,uint32_t index_count,const void* index_data);
		~VertexArrayObject();

		void Bind();
		void UnBind();

		void BindVertexAttrib(const VertexAttrib& attrib);
		void UpdateVertexAttrib();
	
		GLuint id() const { return id_; }
		bool IsUseIndex() const { return use_index_; }
		const VertexGpuBufferPtr& vertex_buffer() const { return vertex_buffer_; }
		const IndexGpuBufferPtr& index_buffer() const { return index_buffer_; }
	private:
		RendererPtr renderer_;

		GLuint id_;
		bool use_index_;
		VertexGpuBufferPtr vertex_buffer_;
		IndexGpuBufferPtr index_buffer_;
		std::unordered_map<VertexAttribFormat, VertexAttrib> attrib_map_;
		bool update_attrib_;
	};
}

#endif
