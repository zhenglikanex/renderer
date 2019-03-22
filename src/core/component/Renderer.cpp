#include "Renderer.h"

#include "Context.h"
#include "SceneManager.h"
#include "Mesh.h"
#include "SubMesh.h"

namespace aurora
{
	IComponentPtr Renderer::Clone()
	{

	}

	void Renderer::Copy(const IComponentPtr& component)
	{

	}

	void Renderer::Start()
	{

	}

	void Renderer::Update()
	{
		for(auto& submesh : mesh_->submeshs())
		{
			if (!submesh->IsActive())
			{
				Context::GetInstance()->scene_manager()->AddRenderQuene(submesh);
			}
			
			submesh->AddInstance(GetGameObject());
		}
	}

	void Renderer::Dispose()
	{
		
	}
}

