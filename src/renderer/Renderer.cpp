#include "Renderer.h"
#include "DeviceContext.h"

namespace aurora 
{
	Renderer::Renderer(const Config& config)
		:config_(config)
	{

	}

	Renderer::~Renderer()
	{

	}

	bool Renderer::Initialize()
	{
		auto width = config_.GetInt("width");
		auto height = config_.GetInt("height");
		device_context_ = MakeDeviceContextPtr(config_.GetString("title"),width,height);
		if (!device_context_ || device_context_->Initlized())
		{
			LOG_ERROR() << "DeviceContext´´½¨Ê§°Ü!" << LOG_END();
			return true;
		}
		ChangeViewprot(0,0,width, height);
		glClearColor(1.0, 0.0, 0.0, 1.0);

		return true;
	}

	void Renderer::Destory()
	{
		
	}

	void Renderer::Render()
	{
		//
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		device_context_->PollEvents();
	}

	void Renderer::ChangeViewprot(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		viewprot_width_ = width;
		viewprot_height_ = height;
		glViewport(0, 0, viewprot_width_, viewprot_height_);
	}
}