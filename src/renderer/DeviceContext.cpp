#include "DeviceContext.h"
namespace aurora
{
	DeviceContext::DeviceContext(const std::string& title, uint32_t width, uint32_t height)
		:title_(title),width_(width),height_(height)
	{

	}

	DeviceContext::~DeviceContext()
	{
		std::cout << "DeviceContext::~DeviceContext()" << std::endl;
	}

	bool DeviceContext::Initialized()
	{
		window_ = MakeGLFW3WindowPtr(title_,width_,height_);
		if (!window_ || !window_->Initialized())
		{
			LOG_ERROR() << "window´´½¨Ê§°Ü!" << LOG_END();
			return false;
		}

		return true;
	}

	void DeviceContext::Destory()
	{

	}

	void DeviceContext::SwapBuffers()
	{
		window_->SwapBuffers(); 
	}

	void DeviceContext::PollEvents()
	{
		window_->PollEvents();
	}
}
