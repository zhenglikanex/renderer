#ifndef RENDER_QUENE_H_
#define RENDER_QUENE_H_

#include <vector>
#include <unordered_map>

#include "AuroraDef.h"

namespace aurora
{
	class RenderQueue
	{
		using _RenderQueue = std::vector<std::pair<MaterialPtr, RenderCommandPtr>>;
		using InstanceBatchCommandLookUp = std::unordered_map<MaterialPtr, InstanceBatchCommandPtr>;
	public:
		RenderQueue() {

		}

		const _RenderQueue::iterator begin() { 
			return render_queue_.begin(); 
		}
		const _RenderQueue::iterator end() { return render_queue_.end(); }

		void sort();
		void clear();

		void AddRenderCommand(const RenderCommandPtr& render_command);
		InstanceBatchCommandPtr GetInstanceBatchCommand(const MaterialPtr& material);
	private:
		_RenderQueue render_queue_;
		InstanceBatchCommandLookUp instance_batch_command_lookup_;
	};
}


#endif
