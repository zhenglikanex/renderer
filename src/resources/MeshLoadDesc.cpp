#include "MeshLoadDesc.h"

#include "Mesh.h"
#include "SubMesh.h"
#include "GpuBuffer.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"
#include "VertexTypes.h"
#include "VertexArrayObject.h"
#include "FileHelper.h"

#include <numeric>

#include "glm/glm.hpp"

#include "glSupport.h"

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

	SubMeshPtr MeshLoadDesc::ProcessSubMesh(aiMesh * ai_mesh, const aiScene *scene)
	{

		std::vector<V_P3_N3_T2> vertexs;
		{
			

			//GpuBuffer::Mapper mapper(stream.vertex_buffer,0, stream.vertex_buffer->size(),GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			//auto pointer = mapper.Pointer<V_P3_N3_T2>();

			V_P3_N3_T2 vertex;
			for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
			{
				vertex.position = glm::vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z);
				vertex.normal = glm::vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z);
				vertex.texcoords = glm::vec2(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y);
				//vertex.tangent = glm::vec3(ai_mesh->mTangents[i].x, ai_mesh->mTangents[i].y, ai_mesh->mTangents[i].z);
				//vertex.bitangent = glm::vec3(ai_mesh->mBitangents[i].x, ai_mesh->mBitangents[i].y, ai_mesh->mBitangents[i].z);
				//memcpy(pointer, &vertex, sizeof(vertex));
				//++pointer;
				vertexs.push_back(vertex);
			}
			
			//stream.vertex_buffer->WriteBuffer(0, vertexs.size() * VertexSize(VertexType::kV_P2_T2), data);
		}
		void* data = malloc(vertexs.size() * VertexSize(VertexType::kV_P3_N3_T2));
		memcpy(data, (void*)vertexs.data(), vertexs.size() * VertexSize(VertexType::kV_P3_N3_T2));
		VertexArrayObject::VertexStream stream;
		stream.vertex_buffer = MakeVertexGpuBufferPtr(VertexType::kV_P3_N3_T2, VertexSize(VertexType::kV_P3_N3_T2), ai_mesh->mNumVertices, data);
		stream.attribs.emplace_back(VertexAttribIndex::kPosition, 3, GL_FLOAT, GL_FALSE, 0);
		stream.attribs.emplace_back(VertexAttribIndex::kNoraml, 3, GL_FLOAT, GL_FALSE, offsetof(V_P3_N3_T2, normal));
		stream.attribs.emplace_back(VertexAttribIndex::kTexCoords, 2, GL_FLOAT, GL_FALSE, offsetof(V_P3_N3_T2, texcoords));
		
		std::vector<uint32_t> indces;
		// 如果顶点个数超过2^16使用32bit
		auto index_type = ai_mesh->mNumVertices > std::numeric_limits<uint16_t>::max() ? IndexType::k32Bit : IndexType::k32Bit;
		
		{
			//现在通过每个网格的面（一个面是一个网格它的三角形）并检索相应的顶点索引
			//GpuBuffer::Mapper mapper(index_buffer, 0, index_buffer->size(), GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			if (index_type == IndexType::k16Bit)
			{
				//auto pointer = mapper.Pointer<uint16_t>();
				for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i)
				{
					aiFace face = ai_mesh->mFaces[i];
					for (uint32_t j = 0; j < face.mNumIndices; ++j)
					{
						uint16_t index = face.mIndices[j];
						//memcpy(pointer, &index,sizeof(index));
						//++pointer;
						indces.push_back(index);
					}
				}
			}
			else
			{
				//auto pointer = mapper.Pointer<uint32_t>();
				for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i)
				{
					aiFace face = ai_mesh->mFaces[i];
					for (uint32_t j = 0; j < face.mNumIndices; ++j)
					{
						//memcpy(pointer, &face.mIndices[j], sizeof(face.mIndices[j]));
						//++pointer;
						indces.push_back(face.mIndices[j]);
					}
				}
			}
		}
		void* data1 = malloc(indces.size() * sizeof(uint32_t));
		memcpy(data1, (void*)indces.data(), indces.size() * sizeof(uint32_t));
		auto index_buffer = MakeIndexGpuBufferPtr(index_type, IndexSize(index_type), ai_mesh->mNumFaces * 3, data1);
		//index_buffer->WriteBuffer(0, indces.size() * sizeof(uint32_t), data1);

		auto vao = MakeVertexArrayObjectPtr();
		vao->set_vertex_stream(stream);
		vao->set_index_buffer(index_buffer);

		auto submesh = MakeSubMeshPtr();
		submesh->set_vao(vao);

		return submesh;
	}

	void MeshLoadDesc::ProcessNode(const MeshPtr& mesh, aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
			mesh->AddSubMesh(ProcessSubMesh(ai_mesh, scene));
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