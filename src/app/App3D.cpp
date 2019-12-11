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
			LOG_ERROR() << "Context初始化失败!" << LOG_END();
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
		// 更新游戏
		OnUpdate();

		InputManager::GetInstance()->Update();

		// 处理引擎循环
		Context::GetInstance()->Update();
	}

	void App3D::Run()
	{
		// 第一帧时间设置为理想值;
		Global::s_delta_frame_time = fps_interval_;

		while(!Context::GetInstance()->quit())
		{
			Clock begin_clock;

			// 更新游戏
			Update();
			
			Clock end_clock;

			// 将当前帧时间估算为上一帧时间
			Global::s_delta_frame_time = end_clock - begin_clock;

			// 如果当前消耗时间小于设置的帧数则沉睡线程
			if (Global::s_delta_frame_time < fps_interval_)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>((fps_interval_ - Global::s_delta_frame_time) * 1000)));

				Global::s_delta_frame_time = fps_interval_;
			}

			fps_ = static_cast<int>(std::ceil(1.0f / Global::s_delta_frame_time));
		}

		// 释放资源
		Destory();
	}
}
