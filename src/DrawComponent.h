#pragma once

#include "IComponent.h"
#include <array>
#include "glm/glm.hpp"

namespace aurora
{
	class DrawComponent : public IComponent
	{
	public:
		DrawComponent();
		~DrawComponent(){}

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override;
		void Update() override;
		void Dispose() override;
	private:
		MeshPtr mesh_;
		std::array<glm::vec3, 3> postions_;
		std::array<uint32_t, 3> indexs_;
	};
}