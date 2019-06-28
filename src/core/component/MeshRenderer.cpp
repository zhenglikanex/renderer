#include "MeshRenderer.h"

#include "Context.h"
#include "SceneManager.h"
#include "Mesh.h"
#include "SubMesh.h"

namespace aurora
{
	IComponentPtr MeshRenderer::Clone()
	{

	}

	void MeshRenderer::Copy(const IComponentPtr& component)
	{

	}

	void MeshRenderer::Start()
	{

	}

	void MeshRenderer::Update()
	{
		//for(auto& submesh : mesh_->submeshs())
		//{
		//	if (!submesh->IsActive())
		//	{
		//		Context::GetInstance()->scene_manager()->AddRenderQuene(submesh);
		//	}
		//	
		//	//submesh->AddInstance(GetGameObject());
		//}
		
	}

	void MeshRenderer::Dispose()
	{
		
	}
}

