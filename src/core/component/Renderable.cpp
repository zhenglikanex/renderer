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
			auto pointer = mapper.Pointer<glm::mat4>();
			for (auto& instance : instances_)
			{
				auto model_matrix = instance->GetComponent<SceneNode>()->GetWorldMatrix();
				memcpy(pointer, &model_matrix, sizeof(glm::mat4));
				++pointer;
			}
			
			
		}
	}

	void Renderable::Render()
	{
		BeginRender();

		Context::GetInstance()->render_system()->Render(material_,vao_);

		EndRender();
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