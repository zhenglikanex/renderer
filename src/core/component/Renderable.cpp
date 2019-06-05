#include "Renderable.h"

#include "RenderSystem.h"
#include "GpuBuffer.h"
#include "VertexArrayObject.h"
#include "Material.h"
#include "Shader.h"
#include "GameObject.h"
#include "SceneNode.h"
#include "Context.h"
#include "SceneManager.h"
#include "Camera.h"


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
		if (instances_.size() > 1)
		{
			GLsizeiptr size = instances_.size() * sizeof(glm::mat4) + instances_.size();

			auto instance_stream = vao_->instance_stream();
			if (!instance_stream.instance_buffer)
			{
				instance_stream.instance_buffer = MakeGpuBufferPtr(GL_ARRAY_BUFFER, size, GL_DYNAMIC_DRAW, nullptr);
			}
			else if (instance_stream.instance_buffer->size() != size)
			{
				instance_stream.instance_buffer->Resize(size);
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
				instance_stream.attribs.emplace_back(VertexAttribIndex::kInstanceModelMatrix1 + index, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * index);
			}
			for (uint32_t index = 0; index <= 3; ++index)
			{
				instance_stream.attribs.emplace_back(VertexAttribIndex::kInstanceNormalMatrix1 + index, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) + sizeof(glm::vec3) * index);
			}
			instance_stream.size = sizeof(InstanceData);

			vao_->set_instance_stream(instance_stream);
		}

		auto camera = Context::GetInstance()->scene_manager()->cur_camera();
		auto shader = material_->shader();
		shader->CommitMat4(ShaderUniform::ProjMatrix, camera->GetProjectionMatrix());
		shader->CommitMat4(ShaderUniform::ViewMatrix, camera->GetViewMatrix());
		shader->CommitMat4(ShaderUniform::VPMatrix, camera->GetProjectionMatrix() * camera->GetViewMatrix());
	}

	void Renderable::Render()
	{
		Context::GetInstance()->render_system()->Render(material_,render_mode_,vao_,instances_.size());
	}

	void Renderable::EndRender()
	{

	}

	void Renderable::ClearInstance()
	{
		instances_.clear();
		
	}

	void Renderable::AddInstance(const GameObjectPtr& go)
	{
		instances_.push_back(go);
	}

	size_t Renderable::GetInstanceNum()
	{
		return instances_.size();
	}
}