#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "AuroraDef.h"

namespace aurora
{
	class Renderable
	{
	public:
		Renderable();
		virtual ~Renderable() = 0;

		virtual void BeginRender();

		// œÚRenderSystemÃ·Ωª‰÷»æ
		virtual void Render();

		virtual void EndRender();

		void ClearInstance();
		void AddInstance(const GameObjectPtr& go);
		void GetInstanceNum();

		void set_active(bool active) { active_ = active; }
		bool IsActive() const { return active_; }

		void set_vao(const VertexArrayObjectPtr& vao) { vao_ = vao; }
		const VertexArrayObjectPtr& vao() const { return vao_; }

		void set_material(const MaterialPtr& material) { material_ = material; }
		const MaterialPtr& material() const { return material_; }
	private:
		bool active_;
		VertexArrayObjectPtr vao_;
		MaterialPtr material_;
		std::vector<GameObjectPtr> instances_;
	};
}

#endif
