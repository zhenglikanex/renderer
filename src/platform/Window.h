#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "Aurora.h"

namespace aurora
{
	class Window
	{
	public:
		Window(const std::string& title_name,uint32_t width,uint32_t height)
			:title_name_(title_name),width_(width),height_(height)
		{ }

		virtual ~Window() = 0 {}

		virtual bool Initlized() = 0;
		virtual void Destory() = 0;

		virtual void SwapBuffers() = 0;

		virtual void PollEvents() = 0;

		void set_width(uint32_t width) { width_ = width; }
		uint32_t width() const { return width_; }

		void set_height(uint32_t height) { height_ = height; }
		uint32_t height() const { return height_; }
	protected:
		std::string title_name_;
		uint32_t width_;
		uint32_t height_;
	};
}

#endif