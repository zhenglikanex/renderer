#include "ISceneNode.h"

#include "StringUtil.h"
#include "GameObject.h"

#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	ISceneNode::ISceneNode()
		: model_matrix_(glm::identity<glm::mat4>())
		, need_update_matrix_(false)
	{

	}

	ISceneNode::~ISceneNode()
	{

	}

	void ISceneNode::Copy(const IComponentPtr& component)
	{
		IComponent::Copy(component);

		auto scene_node = std::dynamic_pointer_cast<ISceneNode>(component);
		if (scene_node)
		{
			scene_node->need_update_matrix_ = need_update_matrix_;
			scene_node->model_matrix_ = model_matrix_;
		}
	}

	IComponentPtr ISceneNode::Clone()
	{
		auto scene_node = MakeISceneNodePtr();
		return scene_node;
	}

	void ISceneNode::Update()
	{

	}

	void ISceneNode::AddChild(const GameObjectPtr& game_object)
	{
		auto scene_node = game_object->GetComponent<ISceneNode>();
		if (scene_node)
		{
			scene_node->parent_ = shared_from_this()->GetGameObject();
			children_.emplace_back(game_object);
		}
	}

	void ISceneNode::AddChild(const ISceneNodePtr& node)
	{
		auto game_object = node->GetGameObject();
		if (game_object)
		{
			node->parent_ = shared_from_this()->GetGameObject();
			children_.emplace_back(std::move(game_object));
		}
	}

	ISceneNodePtr ISceneNode::FindByName(const std::string& name) const
	{
		for (auto& child : children_)
		{
			if (child->name() == name)
			{
				return child->GetComponent<ISceneNode>();
			}
		}

		return ISceneNodePtr();
	}

	ISceneNodePtr ISceneNode::Find(const std::string& name) const
	{
		auto child_names = StringUtil::split(name, '/');
		if (child_names.size() <= 0)
		{
			return nullptr;
		}

		auto current_node = FindByName(child_names[0]);
		if (current_node)
		{
			for (int i = 1; i < child_names.size(); ++i)
			{
				current_node = current_node->FindByName(child_names[i]);
				if (!current_node)
				{
					return nullptr;
				}
			}
		}

		return current_node;
	}

	ISceneNodePtr ISceneNode::GetParent() const
	{
		auto parent_game_object = parent_.lock();
		if (!parent_game_object)
		{
			return nullptr;
		}
		return parent_game_object->GetComponent<ISceneNode>();
	}

	std::vector<ISceneNodePtr> ISceneNode::GetChildren() const
	{
		std::vector<ISceneNodePtr> nodes;
		for (auto& child : children_)
		{
			nodes.emplace_back(child->GetComponent<ISceneNode>());
		}

		return nodes;
	}

	glm::mat4 ISceneNode::GetWorldMatrix()
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

	glm::mat3 ISceneNode::GetNormalMatrix()
	{
		return glm::mat3(glm::inverse(GetWorldMatrix()));
	}

}