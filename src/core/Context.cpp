#include "Context.h"

#include "LogManager.h"

namespace aurora
{
	Context::Context()
	{
	}

	Context::~Context()
	{

	}

	bool Context::Initialize()
	{
		// 加载引擎默认配置
		if (!config_.Load("aurora.config"))
		{
			LOG_ERROR() << "aurora.config加载失败!" << LOG_END();
		}

		// 创建renerer
		/*ogl_renderer_ = MakeOGLRendererPtr(config_ptr_);
		if(!ogl_renderer_ || !ogl_renderer_->Initialize())
		{
			LOG_ERROR() << "OGLRenderer Initalize failed!" << LOG_END();
			return false;
		}*/

		// 创建默认资源
		//Resources::GetInstance()->CreateDefaultMaterial();
		//Resources::GetInstance()->CreateDefaultShader();

		return true;
	}

	void Context::Destory()
	{

	}

	void Context::Update()
	{
		
	}
}