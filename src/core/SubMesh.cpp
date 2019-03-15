#include "SubMesh.h"

#include "Mesh.h"

namespace aurora
{
	
	SubMesh::SubMesh(const VertexArrayObjectPtr& vao)
		: vao_(vao)
		, render_type_(GL_TRIANGLES)
	{

	}

	SubMesh::~SubMesh()
	{
		
	}

	RenderOperation SubMesh::GetRenderOperation() const
	{
		return { render_type_ ,vao_ };
	}
}