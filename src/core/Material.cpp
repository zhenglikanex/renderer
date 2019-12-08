#include "Material.h"

#include "Shader.h"
#include "Texture.h"

namespace aurora
{

	Material::Material(const ShaderPtr& shader)
		:shader_(shader)
		,instanced_(false)
	{

	}

	Material::~Material()
	{
	}

	MaterialPtr Material::Clone() const
	{
		auto mtl = MakeMaterialPtr(this->shader_);
		mtl->texture_map_ = this->texture_map_;
		mtl->uniform_value_map_ = this->uniform_value_map_;

		return mtl;
	}

	void Material::AttachTexture(const std::string& name,const TexturePtr& texture)
	{
		if (texture)
		{
			texture_map_.insert(std::make_pair(name, texture));
		}	
	}

	TexturePtr Material::GetTexture(const std::string& name)
	{
		auto iter = texture_map_.find(name);
		if (iter != texture_map_.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	void Material::CommitBool(const std::string& name, bool value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kBool;
		uniform.Bool = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitInt(const std::string& name, int value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kInt;
		uniform.Int = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitUInt(const std::string& name, uint32_t value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUInt;
		uniform.UInt = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitFloat(const std::string& name, float value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kFloat;
		uniform.Float = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitVec3(const std::string& name, const glm::vec3& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kMat3;
		uniform.Vec3 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitVec4(const std::string& name, const glm::vec4& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kVec4;
		uniform.Vec4 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitMat3(const std::string& name, const glm::mat3& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kMat3;
		uniform.Mat3 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitMat4(const std::string& name, const glm::mat4& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kMat4;
		uniform.Mat4 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::Bind()
	{
		shader_->Bind();

		int texture_unit = 0;
		// 提交当前material包含的纹理
		for (auto iter = texture_map_.cbegin(); iter != texture_map_.cend(); ++iter)
		{
			auto name = iter->first;
			auto texture = iter->second;

			if (name.size() > 0)
			{	
				// 绑定纹理对象到纹理单元
				texture->Bind(texture_unit);

				// 提交纹理单元到对应的uniform变量
				shader_->CommitInt(name, texture_unit);

				++texture_unit;
			}
		}

		// 提交材质参数
		for (auto iter = uniform_value_map_.cbegin(); iter != uniform_value_map_.cend(); ++iter)
		{
			shader_->CommitUniform(iter->first, iter->second);
		}
	}

	void Material::UnBind()
	{
		shader_->UnBind();
	}
}
