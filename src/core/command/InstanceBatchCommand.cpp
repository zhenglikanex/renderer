#include "InstanceBatchCommand.h"
#include "GameObject.h"
#include "Context.h"
#include "Shader.h"
#include "Material.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SceneNode.h"
#include "GpuBuffer.h"
#include "VertexArrayObject.h"

#include "glm/glm.hpp"

namespace aurora
{
	InstanceBatchCommand::InstanceBatchCommand(GLenum render_mode, const VertexArrayObjectPtr& vao, const MaterialPtr& material)
		:RenderCommand(render_mode,vao,material)
	{

	}

	void InstanceBatchCommand::BeginRender()
	{
		SetupInstanceStream();
		SetupShaderUniform();
	}

	void InstanceBatchCommand::EndRender()
	{

	}

	void InstanceBatchCommand::SetupInstanceStream()
	{
		if (instances_.size() > 1)
		{
			GLsizeiptr size = instances_.size() * sizeof(glm::mat4) + instances_.size() * sizeof(glm::mat3);

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
	}

	void InstanceBatchCommand::SetupShaderUniform()
	{
		auto camera = Context::GetInstance()->scene_manager()->cur_camera();
		auto shader = material_->shader();
		shader->CommitMat4(ShaderUniform::ProjMatrix, camera->GetProjectionMatrix());
		shader->CommitMat4(ShaderUniform::ViewMatrix, camera->GetViewMatrix());
		shader->CommitMat4(ShaderUniform::VPMatrix, camera->GetProjectionMatrix() * camera->GetViewMatrix());
	}
}