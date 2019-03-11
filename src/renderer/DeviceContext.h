#ifndef DEVICE_CONTEXT_H_
#define DEVICE_CONTEXT_H_

#include <string>

#include "AuroraDef.h"
#include "Aurora.h"
#include "glad/glad.h"
#include "GLFW3Window.hpp"

namespace aurora
{
	class DeviceContext
	{
	public:
		DeviceContext(const std::string& title,uint32_t width,uint32_t height);
		~DeviceContext();

		bool Initialized();
		void Destory();

		void SwapBuffers();
		void PollEvents();
		const WindowPtr& window() { return window_; }
	private:
		std::string title_;
		uint32_t width_;
		uint32_t height_;
		WindowPtr window_;
	};
}

#endif
