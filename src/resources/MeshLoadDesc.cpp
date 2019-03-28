#include "MeshLoadDesc.h"

#include "Mesh.h"
#include "SubMesh.h"
#include "VertexTypes.h"
#include "VertexArrayObject.h"
#include "FileHelper.h"

#include "glm/glm.hpp"

namespace aurora
{
	MeshLoadDesc::MeshLoadDesc(const std::string& name)
	{
		name_ = name;
	}

	MeshLoadDesc::~MeshLoadDesc()
	{

	}
	Texture2DPtr MeshLoadDesc::GetTexture(aiMaterial *mat, aiTextureType type)
	{
		// 目前只支持一张纹理
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			auto texture = nullptr;// = LoadTexture2D(directory_ + "/" + str.C_Str());
			return texture;
		}

		return nullptr;
	}

	MaterialPtr MeshLoadDesc::ProcessMaterail(aiMaterial *mat)
	{
		auto tex_diffuse = GetTexture(mat, aiTextureType_DIFFUSE);
		auto tex_noraml = GetTexture(mat, aiTextureType_NORMALS);
		auto tex_specular = GetTexture(mat, aiTextureType_SPECULAR);

		if (tex_diffuse && tex_noraml && tex_specular)
		{

		}

		return nullptr;
	}

	SubMeshPtr MeshLoadDesc::ProcessSubMesh(const MeshPtr& mesh_ptr, aiMesh * ai_mesh, const aiScene *scene)
	{
		auto submesh = MakeSubMeshPtr();
		auto vao = MakeVertexArrayObjectPtr();

		auto vertex_buffer = MakeVertexGpuBufferPtr(sizeof(V_P3_N3_T2);


		V_P3_N3_T2 vertex;
		for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
		{
			vertex.position = glm::vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z);
			vertex.normal = glm::vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z);
			vertex.texcoords = glm::vec2(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y);
			//vertex.tangent = glm::vec3(ai_mesh->mTangents[i].x, ai_mesh->mTangents[i].y, ai_mesh->mTangents[i].z);
			//vertex.bitangent = glm::vec3(ai_mesh->mBitangents[i].x, ai_mesh->mBitangents[i].y, ai_mesh->mBitangents[i].z);

			
		}

		//现在通过每个网格的面（一个面是一个网格它的三角形）并检索相应的顶点索引
		for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i) {
			aiFace face = ai_mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++) {
				indexs.push_back(face.mIndices[j]);
			}
		}

		auto submesh = 

		return submesh_ptr;
	}

	void MeshLoadDesc::ProcessNode(const MeshPtr& mesh, aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
			mesh->AddSubMesh(ProcessSubMesh(mesh, ai_mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(mesh, node->mChildren[i], scene);
		}
	}
	std::shared_ptr<void> MeshLoadDesc::Create()
	{
		auto path = FileHelper::GetInstance()->GetFullPath(name_);
		if (path.empty())
		{
			return nullptr;
		}

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LOG_ERROR() << "Error::ASSIMP::" << importer.GetErrorString() << LOG_END();
			return nullptr;
		}

		MeshPtr mesh = MakeMeshPtr();

		// 保存模型的目录,用于加载纹理
		directory_ = name().substr(0, name_.find_last_of('/'));
		ProcessNode(mesh, scene->mRootNode, scene);

		return mesh;
	}
}