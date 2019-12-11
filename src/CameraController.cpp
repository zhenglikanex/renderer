#include "CameraController.h"
#include "SceneNode.h"
#include "glm/glm.hpp"
#include "Global.h"
#include "InputManager.h"

namespace aurora
{
	CameraController::CameraController()
		:forward_speed_(5)
	{}

	CameraController::~CameraController()
	{

	}

	IComponentPtr CameraController::Clone()
	{
		return std::make_shared<CameraController>();
	}

	void CameraController::Copy(const IComponentPtr& component)
	{
	}

	void CameraController::Start()
	{
		node_ = GetComponent<SceneNode>();
	}

	void CameraController::Update()
	{
		if (node_) 
		{
			if (InputManager::GetInstance()->GetKey(KEY_W) == InputState::kRepeat)
			{
				auto pos = node_->local_position();
				pos.z -= forward_speed_ * Global::s_delta_frame_time;
				node_->set_local_position(pos);
			}
			else if (InputManager::GetInstance()->GetKey(KEY_S) == InputState::kRepeat)
			{
				auto pos = node_->local_position();
				pos.z += forward_speed_ * Global::s_delta_frame_time;
				node_->set_local_position(pos);
			}
		}
	}

	void CameraController::Dispose()
	{

	}
}