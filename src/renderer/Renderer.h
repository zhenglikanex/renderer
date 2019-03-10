#ifndef RENDERER_H_
#define RENDERER_H_

#include "AuroraDef.h"
#include "Config.h"

namespace aurora
{
	class Renderer
	{
	public:
		Renderer(const Config& config);
		~Renderer();

		bool Initialize();
		void Destory();

		void Render();

		void ChangeViewprot(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		const DeviceContextPtr& device_context() { return device_context_; }
	private:
		Config config_;
		DeviceContextPtr device_context_;
		uint32_t viewprot_width_;
		uint32_t viewprot_height_;
	};
}

#endif