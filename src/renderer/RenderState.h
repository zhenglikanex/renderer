#ifndef RENDERSTATE_H_
#define RENDERSTATE_H_

#include "glad/glad.h"
#include "AuroraDef.h"
#include "Material.h"
#include <memory>
#include <unordered_map>

namespace aurora
{
	//用来管理当前OpenGL的渲染状态,减少状态切换
	class RenderState
	{
	public:
		using BindBufferMap = std::unordered_map<GLenum, GLuint>;
	public:
		RenderState()
		{

		}
		~RenderState()
		{

		}

		void BindVAO(GLuint vao)
		{
			if (bind_vao_ == vao)
			{
				return;
			}
			bind_vao_ = vao;

			glBindVertexArray(bind_vao_);
		}

		void BindBuffer(GLenum target, GLuint id)
		{
			auto iter = bind_buffer_map_.find(target);
			if (iter == bind_buffer_map_.end())
			{
				glBindBuffer(target, id);
				bind_buffer_map_.emplace(target, id);
			}
			else if (iter->second != id)
			{
				glBindBuffer(target, id);
				iter->second = id;
			}
		}

		void BindMaterial(const MaterialPtr& material)
		{
			if (bind_material_ || bind_material_.get() != material.get())
			{
				bind_material_->Bind();
			}
		}
	private:
		GLuint bind_vao_;
		BindBufferMap bind_buffer_map_;
		MaterialPtr bind_material_;
	};
}

#endif
