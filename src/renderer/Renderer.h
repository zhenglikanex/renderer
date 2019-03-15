#ifndef RENDERER_H_
#define RENDERER_H_

#include "AuroraDef.h"
#include "Config.h"
#include "RenderOperation.h"

namespace aurora
{
	class Renderer
	{
	public:
		Renderer(const Config& config);
		~Renderer();

		bool Initialized();
		void Destory();

		void Render();


		void ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		uint32_t viewport_width() const { return viewport_width_; }
		uint32_t viewport_height() const { return viewport_height_; }
		const DeviceContextPtr& device_context() { return device_context_; }
		const RendererStatePtr& renderer_state() { return renderer_state_; }
	private:
		void _RenderOperation(const RenderOperation& ro);
	private:

		Config config_;
		uint32_t viewport_width_;
		uint32_t viewport_height_;
		DeviceContextPtr device_context_;
		RendererStatePtr renderer_state_;
	};
}

#endif