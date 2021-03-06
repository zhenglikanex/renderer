#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <vector>

#include "AuroraDef.h"
#include "SceneNode.h"
#include "GameObject.h"
#include "RenderQueue.h"


namespace aurora
{
	class SceneManager
	{

	public:
		SceneManager();
		~SceneManager();

		// 进行场景更新
		void Update();

		const GameObjectPtr& root_node() { return root_node_; }
	public:
		void AddToRootNode(const GameObjectPtr& game_object);

		GameObjectPtr Find(const std::string& name) const;

		template<typename Type>
		std::vector<GameObjectPtr> Find()
		{
			std::vector<GameObjectPtr> game_objects;
			Find<Type>(root_node_, game_objects);
			
			return game_objects;
		}

		void AddRenderQuene(const RenderCommandPtr& command) { return render_queue_.AddRenderCommand(command); }
		InstanceBatchCommandPtr GetInstanceBatchCommand(const MaterialPtr& material) { return render_queue_.GetInstanceBatchCommand(material); }

		const std::vector<CameraPtr>& cameras() const { return cameras_; }
		void set_camera(const GameObjectPtr& camera) { camera_ = camera; }
		const GameObjectPtr& camera() const { return camera_; }
	private:
		template<typename Type>
		void Find(const GameObjectPtr& game_object,std::vector<GameObjectPtr>& game_objects)
		{
			if (!game_object)
			{
				return;
			}

			if (game_object->GetComponent<Type>())
			{
				game_objects.emplace_back(game_object);
			}

			auto node = game_object->GetComponent<SceneNode>();
			if (node)
			{
				for (auto child : node->GetChildren())
				{
					Find<Type>(child->GetGameObject(), game_objects);
				}
			}
		}

		void Visit(const SceneNodePtr& scene_node);
	private:
		GameObjectPtr root_node_;
		std::vector<CameraPtr> cameras_;
		GameObjectPtr camera_;	//当前正在渲染的摄像机
		RenderQueue render_queue_;
	};
}

#endif
