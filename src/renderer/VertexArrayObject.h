#ifndef VERTEX_ARRAY_OBJECT_H_
#define VERTEX_ARRAY_OBJECT_H_

#include <unordered_map>

#include "AuroraDef.h"
#include "Noncopyable.h"
#include "glSupport.h"
#include "VertexTypes.h"

namespace aurora
{
	

	class VertexArrayObject : public Noncopyable
	{
	public:
		struct Attrib
		{
			GLuint index;
			GLint component_num;
			GLenum type;
			GLboolean normalized;
			size_t offset;
		};

		struct VertexStream
		{
			std::vector<Attrib> attribs;
			VertexGpuBufferPtr vertex_buffer;
		};

		struct InstanceStream
		{
			std::vector<Attrib> attribs;
			GpuBufferPtr instance_buffer;
			uint32_t size;
		};
	public:


		VertexArrayObject();
		~VertexArrayObject();

		void Bind();
		void UnBind();

		void UpdateVertexAttrib();

		GLuint id() const { return id_; }
		
		void set_vertex_stream(const VertexStream& vertex_stream) 
		{ 
			vertex_stream_ = vertex_stream; 
			need_update_vertex_stream_ = true;
		}
		const VertexStream& vertex_stream() const { return vertex_stream_; }

		void set_instance_stream(const InstanceStream& instance_stream) { instance_stream_ = instance_stream_; }
		const InstanceStream& instance_stream() const { return instance_stream_; }

		void set_index_buffer(const IndexGpuBufferPtr& index_buffer) { index_buffer_ = index_buffer; }
		const IndexGpuBufferPtr& index_buffer() const { return index_buffer_; }
	private:
		RenderSystemPtr renderer_;

		GLuint id_;
		VertexStream vertex_stream_;
		InstanceStream instance_stream_;
		IndexGpuBufferPtr index_buffer_;
		bool need_update_vertex_stream_;
	};
}

#endif
