#include "Context.h"
#include "LogManager.h"
#include "Renderer.h"

namespace aurora
{
	Context::Context()
	{
	}

	Context::~Context()
	{
		std::cout << "Context::~Context()" << std::endl;
	}

	bool Context::Initialized()
	{
		// ��������Ĭ������
		if (!config_.Load("aurora.config"))
		{
			LOG_ERROR() << "aurora.config����ʧ��!" << LOG_END();
		}

		renderer_ = MakeRendererPtr(config_);
		if (!renderer_ || !renderer_->Initialized())
		{
			LOG_ERROR() << "Renderer��ʼ��ʧ��!" << LOG_END();
		}

		// ����renerer
		/*ogl_renderer_ = MakeOGLRendererPtr(config_ptr_);
		if(!ogl_renderer_ || !ogl_renderer_->Initialized())
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
		renderer_->Render();
	}

	void Context::Quit()
	{
		quit_ = true;
	}
}