#pragma once

#include "AuroraDef.h"
#include "IComponent.h"

namespace aurora {
	class CameraController : public IComponent
	{
	public:
		CameraController();
		virtual ~CameraController();

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override;
		void Update() override;
		void Dispose() override;
	private:
		SceneNodePtr node_;
		float forward_speed_;
	};
}