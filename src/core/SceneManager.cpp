#include "SceneManager.h"

#include <algorithm>

#include "GameObjectFactory.h"
#include "Renderable.h"
#include "Material.h"

namespace aurora
{
	SceneManager::SceneManager()
	{
		//root_node_ = CREATE_GAMEOBJECT(GameObjectFactory::s_kNodeGameObject);
		root_node_->GetComponent<SceneNode>()->set_local_position(glm::vec3(0.0, 0.0, 0.0));
	}

	SceneManager::~SceneManager()
	{
		
	}

	// 进行场景更新
	void SceneManager::Update()
	{
		for(auto& item : render_queue_)
		{
			item.second->ClearInstance();
		}

		render_queue_.clear();

		auto camera_game_objects = Find<Camera>();
		for (auto& camera : camera_game_objects)
		{
			cameras_.push_back(camera->GetComponent<Camera>());
		}

		Visit(root_node_->GetComponent<SceneNode>());

		std::sort(render_queue_.begin(), render_queue_.end(), [](const RenderQueue::value_type& lhs, const RenderQueue::value_type& rhs)
		{
			return lhs.first->Weight() < rhs.first->Weight();
		});

		// 对每个对象进行渲染
		for (const auto& item : render_queue_)
		{
			item.second->Render();
		}
	}

	void SceneManager::AddToRootNode(const GameObjectPtr& game_object)
	{
		if (game_object)
		{
			root_node_->GetComponent<SceneNode>()->AddChild(game_object);
		}
	}

	GameObjectPtr SceneManager::Find(const std::string& name) const
	{
		auto node = root_node_->GetComponent<SceneNode>()->Find(name);
		if (node)
		{
			return node->GetGameObject();
		}

		return GameObjectPtr();
	}

	void SceneManager::AddRenderQuene(const RenderablePtr& renderable)
	{
		if (renderable && renderable->material() && !renderable->IsActive())
		{
			render_queue_.push_back(std::make_pair(renderable->material(),renderable));
			renderable->set_active(true);
		}
	}

	void SceneManager::Visit(const SceneNodePtr& scene_node)
	{
		scene_node->GetGameObject()->Update();

		// TODO：进行场景剔除
		for (auto& child_node : scene_node->GetChildren())
		{
			Visit(child_node);
		}
	}
}