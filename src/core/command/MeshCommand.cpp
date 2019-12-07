#include "MeshCommand.h"
#include "GameObject.h"
#include "Context.h"
#include "Shader.h"
#include "Material.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SceneNode.h"

namespace aurora
{
	MeshCommand::MeshCommand(GLenum render_mode, const VertexArrayObjectPtr& vao, const MaterialPtr& material)
		:RenderCommand(render_mode,vao,material)
	{

	}

	MeshCommand::~MeshCommand()
	{

	}

	void MeshCommand::BeginRender()
	{
		if (instances_.size() <= 0)
		{
			return;
		}

		auto instance = instances_.front();
		auto camera = Context::GetInstance()->scene_manager()->cur_camera();
		auto shader = material_->shader();
		shader->CommitMat4(ShaderUniform::ProjMatrix, camera->GetProjectionMatrix());
		shader->CommitMat4(ShaderUniform::ViewMatrix, camera->GetViewMatrix());
		shader->CommitMat4(ShaderUniform::VPMatrix, camera->GetProjectionMatrix() * camera->GetViewMatrix());
		shader->CommitMat4(ShaderUniform::ModelMatrix, instance->GetComponent<SceneNode>()->GetWorldMatrix());
		shader->CommitMat4(ShaderUniform::NormalMatrix, instance->GetComponent<SceneNode>()->GetNormalMatrix());
	}

	void MeshCommand::EndRender()
	{

	}
}