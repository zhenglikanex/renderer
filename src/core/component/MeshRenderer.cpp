#include "MeshRenderer.h"

#include "Context.h"
#include "Resources.h"
#include "SceneManager.h"
#include "Mesh.h"
#include "SubMesh.h"
#include "InstanceBatchCommand.h"
#include "MeshCommand.h"
#include "Material.h"

namespace aurora
{
	IComponentPtr MeshRenderer::Clone()
	{
		return nullptr;
	}

	void MeshRenderer::Copy(const IComponentPtr& component)
	{

	}

	void MeshRenderer::Start()
	{

	}

	void MeshRenderer::Update()
	{
		auto count = GetSubMeshCount();
		for (auto index = 0; index < count; ++index)
		{
			auto submesh = mesh_->GetSubMeshByIndex(index);
			auto material = GetMaterialByIndex(index);
			if (material->IsInstanced())
			{
				InstanceBatchCommandPtr command = Context::GetInstance()->scene_manager()->GetInstanceBatchCommand(material);
				if (!command)
				{
					command = MakeInstanceBatchCommandPtr(GL_TRIANGLES, submesh->vao(), material);
				}
				command->AddInstance(GetGameObject());
				Context::GetInstance()->scene_manager()->AddRenderQuene(command);
			}
			else
			{
				MeshCommandPtr command = MakeMeshCommandPtr(GL_TRIANGLES, submesh->vao(), material);
				Context::GetInstance()->scene_manager()->AddRenderQuene(command);
			}
		}
	}

	void MeshRenderer::Dispose()
	{
		
	}

	uint32_t MeshRenderer::GetSubMeshCount() const
	{
		if (mesh_)
		{
			return mesh_->GetSubMeshCount();
		}

		return 0;
	}

	MaterialPtr MeshRenderer::GetMaterialByIndex(uint32_t index) const
	{
		auto iter = material_map_.find(index);
		if (iter != material_map_.end())
		{
			return iter->second;
		}

		return nullptr;
	}
	void MeshRenderer::AddMaterial(uint32_t index, const MaterialPtr& material)
	{
		if (index >= GetSubMeshCount())
		{
			return;
		}

		material_map_.emplace(index, material);
	}

	void MeshRenderer::RemoveMaterial(uint32_t index)
	{
		material_map_.erase(index);
	}

	void MeshRenderer::ResetMaterial()
	{
		material_map_.clear();

		auto count = GetSubMeshCount();
		for (uint32_t index = 0; index < count; ++index)
		{
			material_map_.emplace(index, Resources::s_kDefaultMtl);
		}
	}
}

