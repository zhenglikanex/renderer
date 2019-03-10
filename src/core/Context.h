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

		bool Initialize();
		void Destory();

		void Update();
		
		void Quit();

		const RendererPtr& renderer() const { return renderer_; }

		const Config& config() const { return config_; }
	private:
		bool quit_;
		Config config_;
		RendererPtr renderer_;
	};
}

#endif