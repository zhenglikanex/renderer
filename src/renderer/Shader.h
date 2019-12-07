#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <unordered_map>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ShaderType.h"

namespace aurora
{
	struct ShaderUniform
	{
		static const std::string ProjMatrix;
		static const std::string ViewMatrix;
		static const std::string ModelMatrix;
		static const std::string NormalMatrix;
		static const std::string VPMatrix;
		static const std::string MVPMatrix;
	};

	class Shader
	{	
	public:
		// TODO:考虑是否应该把文件读取编译部分代码移到外面
		Shader(const std::string& vs_file,const std::string& fs_file);
		Shader(const std::string& vs_file, const std::string gs_file, const std::string& fs_file);
		~Shader();

		const GLuint id() { return id_; }
	public:
		GLint GetUniformLocation(const std::string& name) const;

		// 提交uniform变量
		void CommitUniform(const std::string& name, const UniformValue& uniform);
		void CommitBool(const std::string& name, GLboolean value);
		void CommitInt(const std::string& name, GLint value);
		void CommitUInt(const std::string& name, GLuint value);
		void CommitFloat(const std::string& name, GLfloat value);
		void CommitVec2(const std::string& name, const glm::vec2& value);
		void CommitVec3(const std::string& name, const glm::vec3& value);
		void CommitVec4(const std::string& name, const glm::vec4& value);
		void CommitMat3(const std::string& name, const glm::mat3& value);
		void CommitMat4(const std::string& name, const glm::mat4& value);

		void Bind();
		void UnBind();
	private:
		void Load(const std::string& vs_file, const std::string& fs_file);
		void Load(const std::string& vs_file, const std::string& gs_file, const std::string& fs_file);
		
		GLuint CreateShader(GLenum type,const std::string& file);

		void CreateProgram(GLint vs_shader,GLint fs_shader);
		void CreateProgram(GLint vs_shader, GLint gs_shader, GLint fs_shader);

		
	private:
		GLuint id_;
		std::string vs_file_;
		std::string gs_file_;
		std::string ps_file_;

		std::unordered_map<std::string, UniformValue> uniforms_;
	};
}

#endif
