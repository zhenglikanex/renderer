#ifndef MESH_COMMAND_H_
#define MESH_COMMAND_H_

#include "RenderCommand.h"

namespace aurora
{
	class MeshCommand : public RenderCommand
	{
	public:
		MeshCommand(GLenum render_mode,const VertexArrayObjectPtr& vao,const MaterialPtr& material);
		virtual ~MeshCommand();

		RenderCommandType type() const override { return RenderCommandType::kMesh; }

		void BeginRender() override;
		void EndRender() override;
	};
}

#endif