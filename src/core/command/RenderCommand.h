#ifndef RENDER_COMMAND_H_
#define RENDER_COMMAND_H_

#include "AuroraDef.h"
#include "glSupport.h"

namespace aurora
{
	enum RenderCommandType
	{
		kMesh,
		kInstance,
	};

	class RenderCommand
	{
	public:
		// non-copy
		RenderCommand(const RenderCommand&) = delete;
		RenderCommand(RenderCommand&&) = delete;
		const RenderCommand& operator=(const RenderCommand&) = delete;
		const RenderCommand& operator=(RenderCommand&&) = delete;

		virtual ~RenderCommand() = 0;
		
		RenderCommandType type() const { return type_; }

		GLenum render_mode() const { return render_mode_; }

		void set_vao(const VertexArrayObjectPtr& vao) { vao_ = vao; }
		const VertexArrayObjectPtr& vao() const { return vao_; }

		void set_material(const MaterialPtr& material) { material_ = material; }
		const MaterialPtr& material() const { return material_; }

	protected:
		RenderCommandType type_;

		GLenum render_mode_;
		VertexArrayObjectPtr vao_;
		MaterialPtr material_;
	};
}

#endif
