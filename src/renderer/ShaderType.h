#ifndef SHADER_TYPE_H_
#define SHADER_TYPE_H_

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace aurora
{
	enum class UniformType
	{
		kUnkowm,
		kBool,
		kInt,
		kUInt,
		kFloat,
		kVec2,
		kVec3,
		kVec4,
		kMat3,
		kMat4,
	};

	struct UniformValue
	{
		UniformType type;
		union
		{
			GLboolean	Bool;
			GLint		Int;
			GLuint		UInt;
			GLfloat		Float;
			glm::vec2	Vec2;
			glm::vec3	Vec3;
			glm::vec4	Vec4;
			glm::mat3	Mat3;
			glm::mat4	Mat4;
		};

		UniformValue():type(UniformType::kUnkowm){}

		bool operator==(const UniformValue& rhs)
		{
			if (type != rhs.type)
			{
				return false;
			}

			switch (type)
			{
			case aurora::UniformType::kUnkowm:
				return true;

			case aurora::UniformType::kBool:
				return Bool == rhs.Bool;

			case aurora::UniformType::kInt:
				return Int == rhs.Int;

			case aurora::UniformType::kUInt:
				return UInt == rhs.UInt;

			case aurora::UniformType::kFloat:
				return Float == rhs.Float;

			case aurora::UniformType::kVec2:
				return Vec2 == rhs.Vec2;

			case aurora::UniformType::kVec3:
				return Vec3 == rhs.Vec3;

			case aurora::UniformType::kVec4:
				return Vec4 == rhs.Vec4;

			case aurora::UniformType::kMat3:
				return Mat3 == rhs.Mat3;

			case aurora::UniformType::kMat4:
				return Mat4 == rhs.Mat4;

			default:
				return false;
			}
		}

		bool operator!=(const UniformValue& rhs)
		{
			return !(*this == rhs);
		}
	};
}

#endif
