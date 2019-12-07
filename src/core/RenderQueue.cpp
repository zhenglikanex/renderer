#include "RenderQueue.h"
#include <algorithm>

#include "Material.h"
#include "RenderCommand.h"
#include "InstanceBatchCommand.h"

namespace aurora
{
	void RenderQueue::sort()
	{
		std::sort(render_queue_.begin(), render_queue_.end(), [](const _RenderQueue::value_type& lhs, const _RenderQueue::value_type& rhs)
		{
			return lhs.first->Weight() < rhs.first->Weight();
		});
	}

	void RenderQueue::clear()
	{
		render_queue_.clear();
		instance_batch_command_lookup_.clear();
	}

	void RenderQueue::AddRenderCommand(const RenderCommandPtr& render_command)
	{
		if (render_command)
		{
			render_queue_.emplace_back(std::make_pair(render_command->material(), render_command));
			if (render_command->type() == RenderCommandType::kInstance)
			{
				instance_batch_command_lookup_.insert(std::make_pair(render_command->material(),std::dynamic_pointer_cast<InstanceBatchCommand>(render_command)));
			}
		}
	}

	InstanceBatchCommandPtr RenderQueue::GetInstanceBatchCommand(const MaterialPtr& material)
	{
		auto iter = instance_batch_command_lookup_.find(material);
		if (iter != instance_batch_command_lookup_.end())
		{
			return iter->second;
		}

		return nullptr;
	}
}
