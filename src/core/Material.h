#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

#include "AuroraDef.h"
#include "ShaderType.h"

namespace aurora
{
	class Material
	{
	public:
		using UniformValueMap = std::unordered_map<std::string, UniformValue>;
		using TextureMap = std::unordered_map<std::string, TexturePtr>;
	public:
		Material(const ShaderPtr& shader);
		~Material();

		uint64_t Weight() { return 0; }

		MaterialPtr Clone() const;

		void AttachTexture(const std::string& name,const TexturePtr& texture);
		TexturePtr GetTexture(const std::string& name);

		void CommitBool(const std::string& name, bool value);
		void CommitInt(const std::string& name, int value);
		void CommitUInt(const std::string& name, uint32_t value);
		void CommitFloat(const std::string& name, float value);
		void CommitVec3(const std::string& name, const glm::vec3& value);
		void CommitVec4(const std::string& name, const glm::vec4& value);
		void CommitMat3(const std::string& name, const glm::mat3& value);
		void CommitMat4(const std::string& name, const glm::mat4& value);

		void Bind();
		void UnBind();

		void set_shader(const ShaderPtr& shader) { shader_ = shader; }
		const ShaderPtr& shader() const { return shader_; }

		const UniformValueMap& uniform_value_map() const { return uniform_value_map_; }
		const TextureMap& texture_map() const { return texture_map_; }
	private:
		ShaderPtr shader_;
		UniformValueMap uniform_value_map_;
		TextureMap texture_map_;
	};
}

#endif
