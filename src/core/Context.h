#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "AuroraDef.h"
#include "Singleton.h"
#include "Config.h"

namespace aurora
{
	class Context :public Singleton<Context>
	{
	public:
		Context();
		~Context();

		bool Initialized();
		void Destory();

		void Update();
		
		void Quit();

		bool quit() const { return quit_; }
		const Config& config() const { return config_; }
		const RendererPtr& renderer() const { return renderer_; }
	private:
		bool quit_;
		Config config_;
		RendererPtr renderer_;
	};
}

#endif