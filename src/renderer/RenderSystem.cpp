#include "RenderSystem.h"
#include "DeviceContext.h"
#include "RenderState.h"
#include "VertexArrayObject.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"
#include "GpuBuffer.h"

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
			LOG_ERROR() << "DeviceContext´´½¨Ê§°Ü!" << LOG_END();
			return true;
		}

		renderer_state_ = MakeRendererStatePtr();

		ChangeViewport(0,0,width, height);
		glEnable(GL_DEPTH_TEST);

		return true;
	}

	void RenderSystem::Destory()
	{
		
	}

	void RenderSystem::Render()
	{
		//
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		device_context_->SwapBuffers();

		device_context_->PollEvents();
	}

	void RenderSystem::ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		viewport_width_ = width;
		viewport_height_ = height;
		glViewport(0, 0, viewport_width_, viewport_height_);
	}

	void RenderSystem::_RenderOperation(const RenderOperation& ro)
	{
		ro.vao->Bind();
		ro.vao->UpdateVertexAttrib();
		if (ro.vao->IsUseIndex())
		{
			if (ro.vao->index_buffer()->index_type() == IndexType::k16Bit)
			{
				glDrawElements(ro.render_type, ro.vao->index_buffer()->index_count(), GL_UNSIGNED_SHORT, 0);
			}
			else 
			{
				glDrawElements(ro.render_type, ro.vao->index_buffer()->index_count(), GL_UNSIGNED_INT, 0);
			}
		}
		else 
		{
			glDrawArrays(ro.render_type, 0, ro.vao->vertex_buffer()->vertex_count());
		}
	}
}