#include "GpuBuffer.h"
#include "RenderSystem.h"
#include "RenderState.h"
#include "Context.h"

namespace aurora
{

	GpuBuffer::GpuBuffer(GLenum target, GLsizeiptr size, GLenum usage, const void* data /* = nullptr */)
		: renderer_(Context::GetInstance()->render_system())
		, target_(target)
		, size_(size)
		, usage_(usage)
	{
		CHECK_GL_ERROR(glGenBuffers(1, &id_));

		Bind();

		CHECK_GL_ERROR(glBufferData(target_, size_, data, usage_));
	}

	GpuBuffer::~GpuBuffer()
	{
		CHECK_GL_ERROR(glDeleteBuffers(1, &id_));
	}

	void GpuBuffer::Bind()
	{
		//renderer_->renderer_state()->BindBuffer(target_,id_);
		glBindBuffer(target_, id_);
	}

	void GpuBuffer::UnBind()
	{
		//renderer_->renderer_state()->BindBuffer(target_, 0);
		glBindBuffer(target_, 0);
	}

	void GpuBuffer::Resize(GLsizeiptr size)
	{
		if (size_ == size)
		{
			glBufferData(target_, size_, nullptr, usage_);
		}
	}

	void GpuBuffer::ReadBuffer(GLintptr offset, GLsizeiptr size, void* data)
	{
		Bind();

		CHECK_GL_ERROR(glGetBufferSubData(target_, offset, size, data));
	}

	void GpuBuffer::WriteBuffer(GLintptr offset, GLsizeiptr size,const void* data)
	{
		Bind();

		if (offset == 0)
		{
			CHECK_GL_ERROR(glBufferData(target_, size, data, usage_));
		}
		else
		{
			CHECK_GL_ERROR(glBufferSubData(target_, offset, size, data));
		}
	}

	void GpuBuffer::DiscardBuffer(GLintptr offset /* = 0 */, GLsizeiptr size /* = 0 */)
	{
		if (offset && size == 0)
		{
			CHECK_GL_ERROR(glInvalidateBufferData(id_));
		}
		else
		{
			CHECK_GL_ERROR(glInvalidateBufferSubData(id_, offset, size));
		}
	}

	void* GpuBuffer::MapBuffer(GLintptr offset,GLsizeiptr size,GLenum access)
	{
		// GL_MAP_INVALIDATE_BUFFER_BIT ����ԭ�ȵĻ���,������GL_MAP_READ_BITͬʱʹ��,���֮��δд�룬�򻺴�����δ����
		// GL_MAP_INVALIDATE_RANGE_BIT  ����ָ����Χ�Ļ���,������GL_MAP_READ_BITͬʱʹ��,���֮��δд�룬�򻺴�����δ����
		// GL_MAP_UNSYNCHRONIZED_BIT	ʹ���Զ�ͬ��(һ�㶼ʹ��)
		// GL_MAP_FLUSH_EXPLICIT_BIT	����Ӧ�ó�����ʾ֪ͨˢ��ӳ������,������GL_MAP_WRITE_BITͬʱʹ��
		AURORA_ASSERT(
			((access & (GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_READ_BIT)) != (GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_READ_BIT)) &&
			((access & (GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_READ_BIT)) != (GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_READ_BIT)) &&
			(((access & GL_MAP_FLUSH_EXPLICIT_BIT) == 0) || ((access & GL_MAP_FLUSH_EXPLICIT_BIT) != 0) && ((access & GL_MAP_WRITE_BIT) != 0)) &&
			"MapBuffer Access Error"
		);

		Bind();

		void* buffer = nullptr;
		CHECK_GL_ERROR(buffer = glMapBufferRange(target_, offset, size, access));

		return buffer;
	}

	bool GpuBuffer::UnMapBuffer()
	{
		Bind();

		bool status;
		CHECK_GL_ERROR(status = glUnmapBuffer(target_));

		return status;
	}

	void GpuBuffer::FlushMappedRangeBuffer(GLintptr offset, GLsizeiptr size)
	{
		Bind();
		CHECK_GL_ERROR(glFlushMappedBufferRange(target_, offset, size));
	}
}