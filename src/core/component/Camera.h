#ifndef CAMERA_H_
#define CAMERA_H_

#include <vector>

#include "AuroraDef.h"
#include "IComponent.h"
#include "GameObject.h"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace aurora
{
	class Camera : public IComponent
	{
	public:
		Camera();
		virtual ~Camera();

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override
		{

		}
		void Update() override
		{

		}

		void Dispose() override
		{

		}
	public:
		glm::mat4x4 GetViewMatrix();
		glm::mat4x4 GetProjectionMatrix();

		void set_yaw(float yaw) { yaw_ = yaw; }
		float yaw() const { return yaw_; }

		void set_pitch(float pitch) { pitch_ = pitch; }
		float pitch() const { return pitch_; }

		void set_fov(float fov) { fov_ = fov; }
		float fov() const { return fov_; }

		void set_screen_width(float screen_width) { screen_width_ = screen_width; }
		float screen_width() const { return screen_width_; }

		void set_screen_height(float screen_height) { screen_height_ = screen_height; }
		float screen_height() const { return screen_height_; }

		void set_near_panel(float near_panel) { near_panel_ = near_panel; }
		float near_panel() const { return near_panel_; }

		void set_far_panel(float far_panel) { far_panel_ = far_panel; }
		float far_panel() const { return far_panel_; }
	private:
		void UpdateCameraVectors();

		glm::vec3 front_;
		glm::vec3 up_;
		glm::vec3 right_;
		glm::vec3 world_up_;

		// Euler Angles;
		float yaw_;
		float pitch_;

		// �Ӿ������
		float fov_;
		float screen_width_;
		float screen_height_;
		float near_panel_;
		float far_panel_;
	};
}

#endif
