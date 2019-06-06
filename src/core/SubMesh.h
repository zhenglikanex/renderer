#ifndef SUBMESH_H_
#define SUBMESH_H_

#include "AuroraDef.h"
#include "glSupport.h"

namespace aurora
{
	class SubMesh
	{
	public:
		SubMesh();
		~SubMesh();

		void set_vao(const VertexArrayObjectPtr& vao) { vao_ = vao; }
		const VertexArrayObjectPtr& vao() const { return vao_; }
	public:
		VertexArrayObjectPtr vao_;
	};
}

#endif
