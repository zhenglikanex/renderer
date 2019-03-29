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

	void RenderSystem::Render(GLenum render_mode,const MaterialPtr& material, const VertexArrayObjectPtr& vao)
	{
		
	}

	void RenderSystem::ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		viewport_width_ = width;
		viewport_height_ = height;
		glViewport(0, 0, viewport_width_, viewport_height_);
	}
}