#include "Context.h"
#include "LogManager.h"
#include "RenderSystem.h"
#include "Resources.h"
#include "SceneManager.h"
#include "GameObjectFactory.h"
#include "InputManager.h"
namespace aurora
{
	Context::Context()
		:quit_(false)
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

		// ��ʼ��
		if (!GameObjectFactory::GetInstance()->Initialized())
		{
			LOG_ERROR() << "GameObjectFactory��ʼ��ʧ��!" << LOG_END();
		}

		render_system_ = MakeRenderSystemPtr(config_);
		if (!render_system_ || !render_system_->Initialized())
		{
			LOG_ERROR() << "RenderSystem��ʼ��ʧ��!" << LOG_END();
		}

		scene_manager_ = MakeSceneManagerUqePtr();
		if (!scene_manager_)
		{
			LOG_ERROR() << "ScenerManager��ʼ��ʧ��!" << LOG_END();
		}

		// ����renerer
		/*ogl_renderer_ = MakeOGLRendererPtr(config_ptr_);
		if(!ogl_renderer_ || !ogl_renderer_->Initialized())
		{
			LOG_ERROR() << "OGLRenderer Initalize failed!" << LOG_END();
			return false;
		}*/

		// ����Ĭ����Դ
		Resources::GetInstance()->CreateDefaultMaterial();
		Resources::GetInstance()->CreateDefaultShader();

		return true;
	}

	void Context::Destory()
	{

	}

	void Context::Update()
	{
		render_system_->BeginRender();
		scene_manager_->Update();
		render_system_->EndRender();
		//render_system_->Render();
	}

	void Context::Quit()
	{
		quit_ = true;
	}
}