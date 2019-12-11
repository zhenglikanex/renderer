#include "GameObject.h"

#include <numeric>

#include "IComponent.h"

namespace aurora
{
	uint64_t GameObject::s_global_game_id = 0;

	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
		auto iter = id_by_component_map_.begin();
		while (iter != id_by_component_map_.end())
		{
			iter->second->Dispose();
			iter = id_by_component_map_.erase(iter);
		}
	}

	void GameObject::Update()
	{
		for (auto& iter : id_by_component_map_)
		{
			iter.second->Update();
		}
	}

	IComponentPtr GameObject::GetComponent(const std::string& id)
	{
		auto iter = id_by_component_map_.find(id);
		if (iter == id_by_component_map_.end()) {
			return IComponentPtr();
		}

		return iter->second;
	}
}