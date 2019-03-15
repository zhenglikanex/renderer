#ifndef SUBMESH_H_
#define SUBMESH_H_

#include "AuroraDef.h"
#include "glSupport.h"
#include "RenderOperation.h"

namespace aurora
{
	class SubMesh
	{
	public:
		SubMesh(const VertexArrayObjectPtr& vao);
		~SubMesh();

		RenderOperation GetRenderOperation() const;

		void set_vao(const VertexArrayObjectPtr& vao) { vao_ = vao; }
		const VertexArrayObjectPtr& vao() const { return vao_; }

		void set_material(const MaterialPtr& material) { material_ = material; }
		const MaterialPtr& material() const { return material_; }

		void set_render_type(GLenum render_type) { render_type_ = render_type; }
		GLenum render_type() const { return render_type_; }
	private:
		VertexArrayObjectPtr vao_;
		MaterialPtr material_;
		GLenum render_type_;
	};
}

#endif
