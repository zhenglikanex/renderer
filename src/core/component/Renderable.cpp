#include "Renderable.h"

#include "RenderSystem.h"
#include "GpuBuffer.h"
#include "VertexArrayObject.h"
#include "GameObject.h"
#include "SceneNode.h"
#include "Context.h"
#include "Material.h"

#include "glm/glm.hpp"

namespace aurora
{
	Renderable::Renderable()
	{
		
	}

	Renderable::~Renderable()
	{

	}

	void Renderable::BeginRender()
	{
		GLsizeiptr size = instances_.size() * sizeof(glm::mat4);

		auto instance_stream = vao_->instance_stream();
		if (!instance_stream.instance_buffer)
		{
			instance_stream.instance_buffer = MakeGpuBufferPtr(GL_ARRAY_BUFFER, size, GL_DYNAMIC_DRAW,nullptr);
		}
		instance_stream.attribs.clear();

		{
			auto mapper = GpuBuffer::Mapper(instance_stream.instance_buffer, 0, size, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
			auto pointer = mapper.Pointer<InstanceData>();
			for (auto& instance : instances_)
			{
				auto model_matrix = instance->GetComponent<SceneNode>()->GetWorldMatrix();
				auto normal_matrix = instance->GetComponent<SceneNode>()->GetNormalMatrix();

				memcpy(pointer, &model_matrix, sizeof(model_matrix));
				memcpy(pointer + offsetof(InstanceData, model_matrix), &normal_matrix, sizeof(normal_matrix));
				++pointer;
			}
		}

		for (uint32_t index = 0; index <= 4; ++index)
		{
			instance_stream.attribs.emplace_back(VertexAttribIndex::kInstanceModelMatrix1 + index, 4, GL_FLOAT, GL_FALSE,sizeof(glm::vec4) * index);
		}
		for (uint32_t index = 0; index <= 3; ++index)
		{
			instance_stream.attribs.emplace_back(VertexAttribIndex::kInstanceNormalMatrix1 + index, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) + sizeof(glm::vec3) * index);
		}
		instance_stream.size = sizeof(InstanceData);

		
	}

	void Renderable::Render()
	{
		Context::GetInstance()->render_system()->Render(material_,vao_);
	}

	void Renderable::EndRender()
	{

	}

	void Renderable::ClearInstance()
	{
		
	}

	void Renderable::AddInstance(const GameObjectPtr& go)
	{
		instances_.push_back(go);

		
	}

	void Renderable::GetInstanceNum()
	{

	}
}