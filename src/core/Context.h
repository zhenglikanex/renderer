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
		const RenderSystemPtr& render_system() const { return render_system_; }
		const SceneManagerUqePtr& scene_manager() const { return scene_manager_; }
	private:
		bool quit_;
		Config config_;
		RenderSystemPtr render_system_;
		SceneManagerUqePtr scene_manager_;
	};
}

#endif