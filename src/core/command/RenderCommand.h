#ifndef RENDER_COMMAND_H_
#define RENDER_COMMAND_H_

#include <vector>

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
		RenderCommand(GLenum render_mode, const VertexArrayObjectPtr& vao, const MaterialPtr& material);

		// non-copy
		RenderCommand(const RenderCommand&) = delete;
		RenderCommand(RenderCommand&&) = delete;
		const RenderCommand& operator=(const RenderCommand&) = delete;
		const RenderCommand& operator=(RenderCommand&&) = delete;

		virtual ~RenderCommand() = 0;
		
		virtual RenderCommandType type() const = 0;

		GLenum render_mode() const { return render_mode_; }

		void set_vao(const VertexArrayObjectPtr& vao) { vao_ = vao; }
		const VertexArrayObjectPtr& vao() const { return vao_; }

		void set_material(const MaterialPtr& material) { material_ = material; }
		const MaterialPtr& material() const { return material_; }

		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
		void Render();

		void AddInstance(const GameObjectPtr& instance) { instances_.push_back(instance); }
		uint32_t GetInstanceNum() const { return instances_.size(); }
	protected:
		GLenum render_mode_;
		VertexArrayObjectPtr vao_;
		MaterialPtr material_;
		std::vector<GameObjectPtr> instances_;
	};
}

#endif
