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
		BindBufferMap bind_buffer_map_;
	};
}

#endif
