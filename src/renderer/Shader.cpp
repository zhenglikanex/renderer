#include "Shader.h"

#include <memory>
#include "FileHelper.h"

namespace aurora
{
	const std::string ShaderUniform::ProjMatrix = "proj_matrix";
	const std::string ShaderUniform::ViewMatrix = "view_matrix";
	const std::string ShaderUniform::ModelMatrix = "model_matrix";
	const std::string ShaderUniform::VPMatrix = "vp_matrix";
	const std::string ShaderUniform::MVPMatrix = "mvp_matrix";

	Shader::Shader(const std::string& vs_file, const std::string& fs_file)
		: vs_file_(vs_file)
		, ps_file_(fs_file)
	{
		Load(vs_file, fs_file);
	}

	Shader::Shader(const std::string& vs_file, const std::string gs_file, const std::string& fs_file)
		:vs_file_(vs_file)
		,gs_file_(gs_file)
		,ps_file_(fs_file)
	{
		Load(vs_file_, gs_file_, ps_file_);
	}

	Shader::~Shader()
	{
		glDeleteProgram(id_);
	}

	GLint Shader::GetUniformLocation(const std::string& name) const
	{
		return glGetUniformLocation(id_, name.c_str());
	}

	void Shader::CommitUniform(const std::string& name, const UniformValue& uniform)
	{
		if (uniform.type == UniformType::kUnkowm)
		{
			return;
		}

		// ÅÐ¶Ï»º´æ
		auto iter = uniforms_.find(name);
		if (iter != uniforms_.end() && iter->second == uniform)
		{
			return;
		}

		// ¸üÐÂ»º´æ
		if (iter == uniforms_.end())
		{
			uniforms_.insert(std::make_pair(name, uniform));
		}
		else 
		{
			iter->second = uniform;
		}

		auto location = GetUniformLocation(name);
		if (location < 0)
		{
			return;
		}

		switch (uniform.type)
		{	
		case aurora::UniformType::kBool:
			glUniform1i(location, (GLint)uniform.Bool);
			break;
		case aurora::UniformType::kInt:
			glUniform1i(location, uniform.Int);
			break;
		case aurora::UniformType::kUInt:
			glUniform1ui(location, uniform.UInt);
			break;
		case aurora::UniformType::kFloat:
			glUniform1f(location, uniform.Float);
			break;
		case aurora::UniformType::kVec2:
			glUniform2fv(location, 1, glm::value_ptr(uniform.Vec2));
		case aurora::UniformType::kVec3:
			glUniform3fv(location, 1, glm::value_ptr(uniform.Vec3));
			break;
		case aurora::UniformType::kVec4:
			glUniform4fv(location, 1, glm::value_ptr(uniform.Vec4));
			break;
		case aurora::UniformType::kMat3:
			glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(uniform.Mat3));
			break;
		case aurora::UniformType::kMat4:
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform.Mat4));
			break;
		default:
			break;
		}
	}

	void Shader::CommitBool(const std::string& name, GLboolean value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kBool;
		uniform.Bool = value;
		CommitUniform(name,uniform);
	}

	void Shader::CommitInt(const std::string& name, GLint value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kInt;
		uniform.Int = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitUInt(const std::string& name, GLuint value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUInt;
		uniform.UInt = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitFloat(const std::string& name, GLfloat value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kFloat;
		uniform.Float = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitVec2(const std::string& name, const glm::vec2& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kVec2;
		uniform.Vec2 = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitVec3(const std::string& name, const glm::vec3& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kVec3;
		uniform.Vec3 = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitVec4(const std::string& name, const glm::vec4& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kVec4;
		uniform.Vec4 = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitMat3(const std::string& name, const glm::mat3& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kMat3;
		uniform.Mat3 = value;
		CommitUniform(name, uniform);
	}

	void Shader::CommitMat4(const std::string& name, const glm::mat4& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kMat4;
		uniform.Mat4 = value;
		CommitUniform(name, uniform);
	}

	void Shader::Bind()
	{
		glUseProgram(id_);
	}
	
	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	void Shader::Load(const std::string& vs_file, const std::string& fs_file)
	{
		auto vs_shader = CreateShader(GL_VERTEX_SHADER, vs_file);
		auto fs_shader = CreateShader(GL_FRAGMENT_SHADER, fs_file);
		CreateProgram(vs_shader, fs_shader);
	}

	void Shader::Load(const std::string& vs_file, const std::string& gs_file, const std::string& fs_file)
	{
		auto vs_shader = CreateShader(GL_VERTEX_SHADER, vs_file);
		auto gs_shader = CreateShader(GL_GEOMETRY_SHADER, gs_file_);
		auto fs_shader = CreateShader(GL_FRAGMENT_SHADER, fs_file);
		CreateProgram(vs_shader, gs_shader, fs_shader);
	}

	GLuint Shader::CreateShader(GLenum type,const std::string& file)
	{
		auto file_identifer = FileHelper::GetInstance()->OpenFileIdentifer(file);
		if (!file_identifer)
		{
			return 0;
		}

		auto source = file_identifer.string();
		const GLchar* c_source = source.c_str();
		GLint size = source.size();

		GLuint id = glCreateShader(type);
		glShaderSource(id, 1, &(c_source), &size);
		glCompileShader(id);

		GLint status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			std::string shader_type;
			if (type == GL_VERTEX_SHADER)
			{
				shader_type = "VertexShader";
			}
			else if (type == GL_GEOMETRY_SHADER)
			{
				shader_type = "GeometryShader";
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				shader_type = "FragmentShader";
			}

			const GLsizei kMaxCount = 256;
			GLchar error_info[kMaxCount + 1] = { 0 };
			GLsizei length;
			glGetShaderInfoLog(id, kMaxCount, &length, error_info);
			
			error_info[length + 1] = '\0';

			LOG_ERROR() << file_identifer.res_name() << shader_type << "±àÒë´íÎó : \n" << error_info << LOG_END();
		}

		return id;
	}


	void Shader::CreateProgram(GLint vs_shader,GLint fs_shader)
	{
		id_ = glCreateProgram();

		if (vs_shader > 0)
		{
			glAttachShader(id_, vs_shader);
		}

		if (fs_shader > 0)
		{
			glAttachShader(id_, fs_shader);
		}

		glLinkProgram(id_);

		GLint status;
		glGetProgramiv(id_, GL_LINK_STATUS, &status);
		if (!status)
		{
			const GLsizei kMaxCount = 256;
			GLchar error_info[kMaxCount + 1] = { 0 };
			GLsizei length;

			glGetProgramInfoLog(id_, kMaxCount, &length, error_info);

			error_info[length + 1] = '\0';

			LOG_ERROR() << "±àÒë³ö´í : \n"
						<< "vs_file: " << vs_file_ << "\n"
						<< "ps_file: " << ps_file_ << "\n"
						<< "error:" << error_info << LOG_END();
		}
		
		glDeleteShader(vs_shader);
		glDeleteShader(fs_shader);
	}

	void Shader::CreateProgram(GLint vs_shader, GLint gs_shader, GLint fs_shader)
	{
		id_ = glCreateProgram();

		if (vs_shader > 0)
		{
			glAttachShader(id_, vs_shader);
		}

		if (gs_shader > 0)
		{
			glAttachShader(id_, gs_shader);
		}

		if (fs_shader > 0)
		{
			glAttachShader(id_, fs_shader);
		}

		glLinkProgram(id_);

		GLint status;
		glGetProgramiv(id_, GL_LINK_STATUS, &status);
		if (!status)
		{
			const GLsizei kMaxCount = 256;
			GLchar error_info[kMaxCount + 1] = { 0 };
			GLsizei length;

			glGetProgramInfoLog(id_, kMaxCount, &length, error_info);

			error_info[length + 1] = '\0';

			LOG_ERROR() << "±àÒë³ö´í : \n"
				<< "vs_file: " << vs_file_ << "\n"
				<< "gs_file: " << gs_file_ << "\n"
				<< "ps_file: " << ps_file_ << "\n"
				<< "error:" << error_info << LOG_END();
		}

		glDeleteShader(vs_shader);
		glDeleteShader(gs_shader);
		glDeleteShader(fs_shader);
	}
}