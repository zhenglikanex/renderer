#include "Camera.h"

#include "SceneNode.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	Camera::Camera()
		:front_(glm::vec3(0.0f, 0.0f, -1.0f))
		, world_up_(glm::vec3(0.0f, 1.0f, 0.0f))
		, yaw_(-90)
		, pitch_(0)
		, fov_(45)
		, screen_width_(1024)
		, screen_height_(768)
		, near_panel_(0.1f)
		, far_panel_(100.0f)
	{
		UpdateCameraVectors();
	}

	Camera::~Camera()
	{

	}

	IComponentPtr Camera::Clone()
	{
		auto camera = MakeCameraPtr();
		return camera;
	}

	void Camera::Copy(const IComponentPtr& component)
	{
		auto camera = std::dynamic_pointer_cast<Camera>(component);
		if (camera)
		{
			camera->front_ = front_;
			camera->up_ = up_;
			camera->right_ = right_;
			camera->world_up_ = world_up_;

			camera->yaw_ = yaw_;
			camera->pitch_ = pitch_;

			camera->fov_ = fov_;
			camera->screen_width_ = screen_width_;
			camera->screen_height_ = screen_height_;
			camera->near_panel_ = near_panel_;
			camera->far_panel_ = far_panel_;
		}
	}

	glm::mat4x4 Camera::GetViewMatrix()
	{
		auto scene_node = GetGameObject()->GetComponent<SceneNode>();
		return glm::lookAt(scene_node->position(), scene_node->position() + front_, up_);
	}

	glm::mat4x4 Camera::GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(fov_), screen_width_ / screen_height_, near_panel_, far_panel_);
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

		front_ = glm::normalize(front);
		right_ = glm::normalize(glm::cross(front, world_up_));
		up_ = glm::normalize(glm::cross(right_, front_));
	}
}