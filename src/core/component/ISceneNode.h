#pragma once

#include <string>
#include <vector>
#include <memory>

#include "AuroraDef.h"
#include "IComponent.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	class ISceneNode : public IComponent, public std::enable_shared_from_this<SceneNode>
	{
	public:
		ISceneNode();
		~ISceneNode();
	public:
		virtual void Update() override;

		void AddChild(const GameObjectPtr& game_object);
		void AddChild(const SceneNodePtr& node);
		ISceneNodePtr FindByName(const std::string& name) const;
		ISceneNodePtr Find(const std::string& name) const;

		ISceneNodePtr GetParent() const;
		std::vector<ISceneNodePtr> GetChildren() const;

		virtual glm::mat4 GetWorldMatrix() = 0;
		virtual glm::mat3 GetNormalMatrix() = 0;

		const glm::mat4& model_matrix() const { return model_matrix_; }

	private:
		virtual void UpdateModelMatrix() = 0;
	private:
		bool need_update_matrix_;
		glm::mat4 model_matrix_;
		GameObjectWeakPtr parent_;
		std::vector<GameObjectPtr> children_;
	};
}
