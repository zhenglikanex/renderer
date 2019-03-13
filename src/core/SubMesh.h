#ifndef SUBMESH_H_
#define SUBMESH_H_

#include "AuroraDef.h"

namespace aurora
{
	class SubMesh
	{
	public:
		SubMesh(const VertexBufferPtr& vertex_buffer, const IndexBufferPtr& index_buffer);
		SubMesh(const VertexBufferPtr& vertex_buffer, const IndexBufferPtr& index_buffer,const MaterialPtr& material_ptr);
		~SubMesh();

		const VertexBufferPtr& vertex_buffer() const { return vertex_buffer_; }
		const IndexBufferPtr& index_buffer() const { return index_buffer_; }

		void set_material(const MaterialPtr& material_ptr) { material_ptr_ = material_ptr; }
		const MaterialPtr& material() const { return material_ptr_; }
	private:
		VertexBufferPtr vertex_buffer_;
		IndexBufferPtr index_buffer_;
		VertexArrayObjectPtr vao_;
		MaterialPtr material_ptr_;
	};
}

#endif
