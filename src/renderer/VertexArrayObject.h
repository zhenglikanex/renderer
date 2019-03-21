#ifndef VERTEX_ARRAY_OBJECT_H_
#define VERTEX_ARRAY_OBJECT_H_

#include <unordered_map>

#include "AuroraDef.h"
#include "Noncopyable.h"
#include "glSupport.h"
#include "VertexTypes.h"

namespace aurora
{
	class VertexAttrib
	{
	public:
		VertexAttrib(VertexAttribFormat format,size_t offset);
		
		VertexAttribFormat format() const { return format_; }
		GLuint inex() const { return format_; }
		GLuint component_num() const { return component_num_; }
		GLenum type() const { return type_; }
		GLboolean normalized() const { return normalized_; }
		size_t offfset() const { return offset_; }
	private:
		VertexAttribFormat format_;
		GLuint index_;
		GLint component_num_;
		GLenum type_;
		GLboolean normalized_;
		size_t offset_;
	};
	class VertexArrayObject : public Noncopyable
	{
	public:
		VertexArrayObject(VertexType vertex_type, uint32_t vertex_count,const void* data);
		VertexArrayObject(VertexType vertex_type, uint32_t vertex_count,const void* vertex_data,IndexType index_type,uint32_t index_count,const void* index_data);
		~VertexArrayObject();

		void Bind();
		void UnBind();

		void BindVertexAttrib(VertexAttribFormat format,size_t offset);
		void UpdateVertexAttrib();
	
		GLuint id() const { return id_; }
		bool IsUseIndex() const { return use_index_; }
		const VertexGpuBufferPtr& vertex_buffer() const { return vertex_buffer_; }
		const IndexGpuBufferPtr& index_buffer() const { return index_buffer_; }
	private:
		RenderSystemPtr renderer_;

		GLuint id_;
		bool use_index_;
		VertexGpuBufferPtr vertex_buffer_;
		IndexGpuBufferPtr index_buffer_;
		std::unordered_map<VertexAttribFormat, VertexAttrib> attrib_map_;
		bool update_attrib_;
	};
}

#endif
