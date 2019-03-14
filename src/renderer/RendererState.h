#ifndef RENDERSTATE_H_
#define RENDERSTATE_H_

#include "glad/glad.h"

#include <unordered_map>

namespace aurora
{
	//用来管理当前OpenGL的渲染状态,减少状态切换
	class RendererState
	{
	public:
		using BindBufferMap = std::unordered_map<GLenum, GLuint>;
	public:
		RendererState()
		{

		}
		~RendererState()
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
				bind_buffer_map_.emplace(target, id);
			}
			else if (iter->second != id)
			{
				glBindBuffer(target, id);
				iter->second = id;
			}
		}
	private:
		GLuint bind_vao_;
		BindBufferMap bind_buffer_map_;
	};
}

#endif
