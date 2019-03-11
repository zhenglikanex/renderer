#include "Renderer.h"
#include "DeviceContext.h"
#include "RendererState.h"

namespace aurora 
{
	Renderer::Renderer(const Config& config)
		:config_(config)
	{

	}

	Renderer::~Renderer()
	{

	}

	bool Renderer::Initialized()
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

	void Renderer::Destory()
	{
		
	}

	void Renderer::Render()
	{
		//
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		device_context_->SwapBuffers();

		device_context_->PollEvents();
	}

	void Renderer::ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		viewport_width_ = width;
		viewport_height_ = height;
		glViewport(0, 0, viewport_width_, viewport_height_);
	}
}