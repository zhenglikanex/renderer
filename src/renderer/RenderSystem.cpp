#include "RenderSystem.h"
#include "DeviceContext.h"
#include "RenderState.h"
#include "VertexArrayObject.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"
#include "GpuBuffer.h"
#include "glm/glm.hpp"
#include <array>

namespace aurora 
{
	RenderSystem::RenderSystem(const Config& config)
		:config_(config)
	{
		
	}

	RenderSystem::~RenderSystem()
	{

	}

	bool RenderSystem::Initialized()
	{
		auto width = config_.GetInt("width");
		auto height = config_.GetInt("height");
		device_context_ = MakeDeviceContextPtr(config_.GetString("title"),width,height);
		if (!device_context_ || !device_context_->Initialized())
		{
			LOG_ERROR() << "DeviceContext����ʧ��!" << LOG_END();
			return true;
		}

		renderer_state_ = MakeRenderStatePtr();

		ChangeViewport(0,0,width, height);
		glEnable(GL_DEPTH_TEST);

		return true;
	}

	void RenderSystem::Destory()
	{
		
	}

	void RenderSystem::BeginRender()
	{
		//
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderSystem::EndRender()
	{
		device_context_->SwapBuffers();
		device_context_->PollEvents();
	}

	void RenderSystem::Render(const MaterialPtr& material, GLenum render_mode, const VertexArrayObjectPtr& vao, GLsizei instance_num)
	{
		material->Bind();
		vao->UpdateVaoToShader();

		if (vao->index_buffer())
		{
			if (instance_num > 1 && vao->instance_stream().instance_buffer)
			{
				if (vao->index_buffer()->index_type() == IndexType::k16Bit)
				{
					CHECK_GL_ERROR(glDrawElementsInstanced(render_mode, vao->index_buffer()->index_num(), GL_UNSIGNED_SHORT, 0, instance_num));
				}
				else
				{
					CHECK_GL_ERROR(glDrawElementsInstanced(render_mode, vao->index_buffer()->index_num(), GL_UNSIGNED_INT, 0, instance_num));
				}
			}
			else
			{
				if (vao->index_buffer()->index_type() == IndexType::k16Bit)
				{
					CHECK_GL_ERROR(glDrawElements(render_mode, vao->index_buffer()->index_num(), GL_UNSIGNED_SHORT, 0));
				}
				else
				{
					CHECK_GL_ERROR(glDrawElements(render_mode, vao->index_buffer()->index_num(), GL_UNSIGNED_INT, 0));
				}
			}
		}
		else
		{
			if (instance_num > 1 && vao->instance_stream().instance_buffer)
			{
				CHECK_GL_ERROR(glDrawArraysInstanced(render_mode, 0, vao->vertex_stream().vertex_buffer->vertex_num(), instance_num));
			}
			else
			{
				CHECK_GL_ERROR(glDrawArrays(render_mode, 0, vao->vertex_stream().vertex_buffer->vertex_num()));
			}
		}
	}

	void RenderSystem::ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		viewport_width_ = width;
		viewport_height_ = height;
		CHECK_GL_ERROR(glViewport(0, 0, viewport_width_, viewport_height_));
	}
}