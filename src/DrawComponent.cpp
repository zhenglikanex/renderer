#include "DrawComponent.h"
#include <array>

#include "glm/glm.hpp"
#include "Mesh.h"
#include "SubMesh.h"
#include "GpuBuffer.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"
#include "VertexTypes.h"
#include "VertexArrayObject.h"
#include "MeshCommand.h"
#include "Context.h"
#include "Resources.h"
#include "SceneManager.h"

namespace aurora
{
	DrawComponent::DrawComponent()
	{
		postions_ = 
		{
			glm::vec3(-0.5,0,0.0),
			glm::vec3(0.0,1.0,0.0),
			glm::vec3(0.5,0.0,0.0)
		};

		indexs_ =
		{
			0,1,2
		};

		VertexArrayObject::VertexStream stream;
		stream.vertex_buffer = MakeVertexGpuBufferPtr(VertexType::kV_P3_N3_T2,sizeof(glm::vec3),postions_.size(),postions_.data());
		stream.attribs.emplace_back(VertexAttribIndex::kPosition, 3, GL_FLOAT, GL_FALSE, 0);

		IndexGpuBufferPtr index_buffer = MakeIndexGpuBufferPtr(IndexType::k32Bit, sizeof(uint32_t), indexs_.size(), indexs_.data());
		
		auto vao = MakeVertexArrayObjectPtr();
		vao->set_vertex_stream(stream);
		vao->set_index_buffer(index_buffer);

		auto submesh = MakeSubMeshPtr();
		submesh->set_vao(vao);

		mesh_ = MakeMeshPtr();
		mesh_->AddSubMesh(submesh);
	}

	IComponentPtr DrawComponent::Clone()
	{
		return std::make_shared<DrawComponent>();
	}

	void DrawComponent::Copy(const IComponentPtr& component)
	{

	}

	void DrawComponent::Start()
	{

	}

	void DrawComponent::Update()
	{
		auto count = mesh_->GetSubMeshCount();
		for (auto index = 0; index < count; ++index)
		{
			auto submesh = mesh_->GetSubMeshByIndex(index);
			auto material = Resources::s_kDefaultMtl;
			MeshCommandPtr command = MakeMeshCommandPtr(GL_TRIANGLES, submesh->vao(), material);
			command->AddInstance(GetGameObject());
			Context::GetInstance()->scene_manager()->AddRenderQuene(command);
		}
	}

	void DrawComponent::Dispose()
	{

	}
}