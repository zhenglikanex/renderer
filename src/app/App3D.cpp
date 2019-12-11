#include "App3D.h"

#include <windows.h>
#include <thread>

#include "Global.h"
#include "Context.h"
#include "Clock.h"
#include "InputManager.h"

namespace aurora
{
	App3D::App3D()
		:fps_(0)
	{
		set_fps_interval(1.0f / 60.0f);
	}

	App3D::~App3D()
	{
	}

	bool App3D::Create()
	{
		if (!Context::GetInstance()->Initialized())
		{
			LOG_ERROR() << "Context��ʼ��ʧ��!" << LOG_END();
			return false;
		}

		return OnCreate();
	}

	void App3D::Destory()
	{
		OnDestory();

		Context::GetInstance()->Destory();
	}

	void App3D::Update()
	{
		// ������Ϸ
		OnUpdate();

		InputManager::GetInstance()->Update();

		// ��������ѭ��
		Context::GetInstance()->Update();
	}

	void App3D::Run()
	{
		// ��һ֡ʱ������Ϊ����ֵ;
		Global::s_delta_frame_time = fps_interval_;

		while(!Context::GetInstance()->quit())
		{
			Clock begin_clock;

			// ������Ϸ
			Update();
			
			Clock end_clock;

			// ����ǰ֡ʱ�����Ϊ��һ֡ʱ��
			Global::s_delta_frame_time = end_clock - begin_clock;

			// �����ǰ����ʱ��С�����õ�֡�����˯�߳�
			if (Global::s_delta_frame_time < fps_interval_)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>((fps_interval_ - Global::s_delta_frame_time) * 1000)));

				Global::s_delta_frame_time = fps_interval_;
			}

			fps_ = static_cast<int>(std::ceil(1.0f / Global::s_delta_frame_time));
		}

		// �ͷ���Դ
		Destory();
	}
}
