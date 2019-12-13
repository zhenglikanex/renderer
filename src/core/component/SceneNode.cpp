#include "SceneNode.h"

#include "StringUtil.h"
#include "GameObject.h"

#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	SceneNode::SceneNode()
		: position_(0, 0, 0)
		, local_position_(0, 0, 0)
		, scale_(1, 1, 1)
		, rotate_(0, 0, 0)
		, model_matrix_(glm::identity<glm::mat4>())
		,need_update_matrix_(false)
	{

	}

	SceneNode::~SceneNode()
	{

	}

	void SceneNode::Copy(const IComponentPtr& component)
	{
		ISceneNode::Copy(component);

		auto scene_node = std::dynamic_pointer_cast<SceneNode>(component);
		if (scene_node)
		{
			scene_node->position_ = position_;
			scene_node->local_position_ = local_position_;
			scene_node->scale_ = scale_;
		}
	}

	IComponentPtr SceneNode::Clone()
	{
		return MakeSceneNodePtr();
	}

	void SceneNode::Start()
	{
		
	}

	void SceneNode::Update()
	{

	}

	void SceneNode::Dispose()
	{
		
	}

	glm::mat4 SceneNode::GetWorldMatrix()
	{
		auto parent = GetParent();
		if (parent)
		{
			return parent->GetWorldMatrix() * model_matrix_;
		}
		else
		{
			return model_matrix_;
		}
	}

	glm::mat3 SceneNode::GetNormalMatrix()
	{
		return glm::mat3(glm::inverse(GetWorldMatrix()));
	}

	void SceneNode::UpdateModelMatrix()
	{
		if (need_update_matrix_)
		{
			
			model_matrix_ = glm::translate(glm::identity<glm::mat4>(), local_position_);
			model_matrix_ = glm::rotate(model_matrix_, glm::radians(rotate_.x), glm::vec3(1, 0, 0));
			model_matrix_ = glm::rotate(model_matrix_, glm::radians(rotate_.y), glm::vec3(0, 1, 0));
			model_matrix_ = glm::rotate(model_matrix_, glm::radians(rotate_.z), glm::vec3(0, 0, 1));
			model_matrix_ = glm::scale(model_matrix_, scale_);

			need_update_matrix_ = false;
		}
	}
}