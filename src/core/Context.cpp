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
		// ��������Ĭ������
		if (!config_.Load("aurora.config"))
		{
			LOG_ERROR() << "aurora.config����ʧ��!" << LOG_END();
		}

		// ����renerer
		/*ogl_renderer_ = MakeOGLRendererPtr(config_ptr_);
		if(!ogl_renderer_ || !ogl_renderer_->Initialize())
		{
			LOG_ERROR() << "OGLRenderer Initalize failed!" << LOG_END();
			return false;
		}*/

		// ����Ĭ����Դ
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